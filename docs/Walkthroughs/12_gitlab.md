# Walkthrough GitLab Example

## Setup
1. Sign-in to GitLab https://gitlab.com
2. Confirm runners are installed.
  - Check `Settings | CI/CD | Runners`
    - Install runners on the local machine if not using GitLab.com
    - Register runner for your project
    - See GitLab.com documentation

## Pipeline Project
1. Create a new project under your username.
    * On the left sidebar, select **Search or go to**.
    * Select **View all my projects**.
    * On the right of the page, select **New project**.
    * Select **Create blank project**.
    * Enter the project details:
        * In the **Project name** field, enter the name of the sample project, for example `SampleProject`.
        * Select **Initialize repository with a README**.
    * Select **Create project**.
2. Create the `.gitlab-ci.yml` file in the project directory.
  - Select `Code | Repository`.
   - Select the current branch, e.g. `main`.
  - Click `+` and select `New file`.
  - Name the file `.gitlab-ci.yml`.
3. Implement a simple pipeline by adding the following into the `.gitlab-ci.yml` file.
```yaml
build-job:
  stage: build
  script:
    - echo "Hello, $GITLAB_USER_LOGIN!"

test-job1:
  stage: test
  script:
    - echo "This job tests something"

test-job2:
  stage: test
  script:
    - echo "This job tests something, but takes more time than test-job1."
    - echo "After the echo commands complete, it runs the sleep command for 20 seconds"
    - echo "which simulates a test that runs 20 seconds longer than test-job1"
    - sleep 20

deploy-prod:
  stage: deploy
  script:
    - echo "This job deploys something from the $CI_COMMIT_BRANCH branch."
  environment: production
```
4. In GitLab commit these changes to run the four jobs that are defined in the `.gitlab-ci.yml` file.

## Examine the Pipeline
1. In GitLab.com select `Build | Pipelines` 
2. Click on the pipeline displayed to see the stages and jobs that make up this pipeline.
3. Watch as the jobs complete and are marked with a green check.
4. Select the job name to view the details.

## Further information
[GitLabs Video](https://www.youtube.com/watch?v=kTNfi5z6Uvk&t=553s)

## Updated the Pipeline
Here is a longer example of a `.gitlab-ci.yml` file.  It starts with a docker image is divided up into two stages and setups up a job for building the application and testing the application which is dependent upon successfully completing the build stage.

```yaml
image: gcc:latest

stages:
  - build
  - test

build_application:
  stage: build
  script:
    - apt-get update && apt-get install -y cmake
    - cmake -G "Unix Makefiles" -S . -B build
    - cmake --build build
  artifacts:
    paths:
      - build/
  only:
    - main

test_application:
  stage: test
  script:
    - ./build/run_tests 
    # Assume the build process generates an executable named run_tests
  dependencies:
    - build_application
  only:
    - main
```
## Explanation
- `stage: test`: This places the job in the `test` stage, which runs after the `build` stage as defined in the `stages` section.

- `script:`: The commands in this section are for running your tests. The example assumes there's an executable named `run_tests` that was generated during the build process and is located in the `build` directory. The actual command you use here will depend on how your testing is set up (for instance, you might be using a testing framework like Google Test).

- `dependencies: - build_application`: This line specifies that the `test_application` job depends on the `build_application` job. This makes the artifacts from `build_application` (the `build/` directory) available for the `test_application` job. If your testing does not require any artifacts from the build stage, you could omit this.