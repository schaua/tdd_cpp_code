# Lab
## CI/CD Pipeline using GitLab

This requires an account on GitLab.com.

## Setup a sample project on GitLab.com
1. Create a new project under your username.
    * On the left sidebar, select `Create new (+)`.
    * Select `Create blank project`.
    * Enter the project details:
        * In the `Project name` field, enter the name of the sample project, for example `TDD Pipeline Lab`.
        * Select `Initialize repository with a README`.
    * Select `Create project`.
2. On the project page, in the upper-right corner select `Code`, **Not** the `</> Code` on the left sidebar, to find the clone paths for the project.  Copy the SSH or HTTP path.

## Create the project locally
1. Open a terminal window on the local machine.  Navigate to where you wish to add the project code.
```bash
cd /c/projects
```
2. Use the path from above to clone the project locally.
```bash
git clone https://gitlab.com/<my-username>/<my-project.git>
```
3. CD into the new project directory.  This is where the project can be built, so copy the existing local project files into this directory to be deployed to GitLab.

4. Commit the changes and push them to GitLab.
```bash
git add --all
git commit -m "Add initial release for project"
git push origin
```
## Begin the CI/CD pipeline configuration  
1. Start with a simple pipeline configuration to ensure that CI/CD is enabled in the project and that the runners are available to run jobs. 
  - Refer to the walkthrough for checking the job runners.  

2.  Create the file `.gitlab-ci.yml` in the root folder of the project.  The job name can be whatever you wish.  Inside the job define a script using the yaml list syntax.
```yaml
test-job:
  script:
    - echo "This is the first job"
    - date
```
3.  Commit and push these changes to GitLab.  

> Jobs represent the work needed to build, test and deploy the project.  Jobs can be organized into stages that execute one after another.  The jobs within a stage can be run in parallel.
Each job identifies a script section that defines the commands for the job.  If there are multiple commands they are run in the order lists.  If the command fails or returns an error the job is flagged as failed and no more commands are run.  

4.  Back in GitLab go to `Build | Pipelines` option in the left sidebar.  Make sure a pipeline runs with this job.  

5.  Select the pipeline, then select the job to view the job's log and see the `This is the first job` message followed by the date.

> The Pipeline Editor is useful to help avoid syntax issues editing the yaml file.  The editor is available in the GitLab page under `Build | Pipeline editor`.  As changes are made they can be committed on the remote repository, **be sure to pull them** down before doing any work is done on the local machine.

## Update the pipeline
1. Replace the content of `.gitlab-ci.yml` with instructions to build the C++ project using CMake.

Below is a basic example of a `.gitlab-ci.yml` file for a GitLab CI/CD pipeline. This configuration defines a job that uses G++ and CMake to build a C++ application. The pipeline runs in a Docker container, and this example uses an image that already has G++ installed.  CMake is installed explicitly, just in case it is not already in the image.

```yaml
image: gcc:latest

stages:
  - build

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
```

Here's what each part does:

- `image: gcc:latest`: This line specifies the Docker image to use for the job. The `gcc:latest` image from Docker Hub comes with GCC installed, which includes G++. Since this image may not have CMake installed, we explicitly install it as part of the build script.

- `stages: - build`: This defines a single stage named `build`. Stages allow you to group jobs and control the order in which they are executed.

- `build_application:`: This is the name of the job. You can name it whatever you like.

- `stage: build`: This assigns the job to the `build` stage.

- `script:`: Under this key, you list the shell commands that make up the job. This example first updates the package lists and installs CMake. Then, it runs CMake to generate the build system.  The image is based on a linux image, so use `Unix Makefiles`.  Finally it runs CMake to compile the application.

- `artifacts: paths: - build/`: This section specifies that the contents of the `build` directory should be saved as artifacts of the build. Artifacts are useful for passing binary files or other build results between stages in a pipeline.

- `only: - main`: This line means the job will only run for commits pushed to the `main` branch. You can adjust this to match your branching strategy, such as including feature branches or tags.

> Note that more complex projects might need to adjust the CMake and make commands with additional arguments, or install more dependencies before building. 

2. Confirm that the pipeline runs and debug any errors.

3.  This course is all about testing, so the work is not complete until we add a job to run the tests that we have created.  
4. To add a test job to the same pipeline, define another job in `.gitlab-ci.yml` , following the `build_application` job. This job is dependent upon the build job completing successfully.  It uses the artifacts produced by the build for testing purposes.   
Below is an extension of the previous example, adding in the `test_application` job as well as an updated `stages:` section that has the *build* stage run first and if successful runs the *test* stage.

```yaml
image: gcc:latest

stages:
  - build
  - test

build_application:
  stage: build
  script:
    - apt-get update && apt-get install -y cmake
    - cmake -G "MinGW Makefiles" -S . -B build
    - cmake --build build
  artifacts:
    paths:
      - build/
  only:
    - main

test_application:
  stage: test
  script:
    - ./build/Demoproject # Assume the build process generates an executable named Demoproject
  dependencies:
    - build_application
  only:
    - main
```

Here are the key points for the `test_application` job:

- `stage: test`: This places the job in the `test` stage, which runs after the `build` stage as defined in the `stages` section.

- `script:`: The commands in this section are for running your tests. The example assumes there's an executable named `Demoproject` that was generated during the build process and is located in the `build` directory. The actual command you use here will depend on how your testing is set up (for instance, you might be using a testing framework like Google Test).  For debugging purposes add a step to the test job `- ls -l ./build` to see what the name of the executable artifact is.

- `dependencies: - build_application`: This line specifies that the `test_application` job depends on the `build_application` job. This makes the artifacts from `build_application` (the `build/` directory) available for the `test_application` job. If your testing does not require any artifacts from the build stage, you could omit this.

- `only: - main`: Similar to the build job, this specifies that the job should only run for the `main` branch.

This setup assumes that the testing executable or script is generated as part of the build process and that it's located in the `build` directory. Modify the `./build/Demoprojects` command based on the project's specific setup, including changing the command or installing additional dependencies required for testing.
5. Confirm that the pipeline runs successfully and that the test output is shown in the logs for the test_application job.  
6. Add a failing test and confirm that the pipeline fails.