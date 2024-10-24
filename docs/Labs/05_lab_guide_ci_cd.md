# Lab
## CI/CD Pipeline using GitLab

This requires an account on GitLab.com.  

## Setup Sample project on GitLab.com
1. Create a new project under your username.
    * On the left sidebar, select **Search or go to**.
    * Select **View all my projects**.
    * On the right of the page, select **New project**.
    * Select **Create blank project**.
    * Enter the project details:
        * In the **Project name** field, enter the name of the sample project.
        * Select **Initialize respository with a README**.
    * Select **Create project**.
2. On the project's overview page, in the upper-right corner select **Code** to find the clone paths for the project.  Copy the SSH or HTTP path and use the path to clone the project locally.
```bash
git clone https://gitlab.com/my-username/my-project.git
```
3. Change to the new project directory, then copy in the files for the project to be deployed.
4. Commit the changes and push them to GitLab.
```bash
git add --all
git commit -m "Add initial release for project"
git push origin
```

## Create the initial CI/CD configuration  
Start the the simplest possible pipeline configuration to ensure that CI/CD is enabled in the project and that the runners are available to run jobs.  
Jobs represent the work needed to build, test and deploy the project.  Jobs can be organized into stages that execute one after another.  The jobs within a stage can be run in parallel.  
Each job identifies a script section that defines the commands for the job.  If there are multiple commands they are run in the order lists.  If the command fails or returns an error the job is flagged as failed and no more commands are run.  
5.  Create a new file `.gitlab-ci.yml` in the root folder of the project.
```yaml
test-job:
  script:
    - echo "This is the first job"
    - date
```
6.  Commit and push these changes to GitLab.
7.  Go to **Build > Pipelines** in GitLab and make sure a pipeline runs with this single job.
8.  Select the pipeline, then select the job to view the job's log and see the `This is the first job` message followed by the date.

## Pipeline Editor
At this point the pipeline editor is useful to help avoid syntax issues with the yaml file.  The editor is available in the GitLab page under **Build > Pipeline editor**.  As changes are made they can be committed on the remote repository, but be sure to pull them down to the local machine before doing any work there.

9. Create a build job for the pipeline
In this step replace the content of `.gitlab-ci.yml` with instructions to build a C++ project using CMake.

Below is a basic example of a `.gitlab-ci.yml` file for a GitLab CI/CD pipeline. This configuration defines a job that uses G++ and CMake to build a C++ application. The pipeline runs in a Docker container, and this example uses an image that already has G++ installed.  CMake is installed explicitly, just in case it is not already in the image.

```yaml
image: gcc:latest

stages:
  - build

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
```

Here's what each part does:

- `image: gcc:latest`: This line specifies the Docker image to use for the job. The `gcc:latest` image from Docker Hub comes with GCC installed, which includes G++. Since this image may not have CMake installed, we explicitly install it as part of the build script.

- `stages: - build`: This defines a single stage named `build`. Stages allow you to group jobs and control the order in which they are executed.

- `build_application:`: This is the name of the job. You can name it whatever you like.

- `stage: build`: This assigns the job to the `build` stage.

- `script:`: Under this key, you list the shell commands that make up the job. This example first updates the package lists and installs CMake. Then, it runs CMake to generate the build system, and finally runs CMake to compile the application.

- `artifacts: paths: - build/`: This section specifies that the contents of the `build` directory should be saved as artifacts of the build. Artifacts are useful for passing binary files or other build results between stages in a pipeline.

- `only: - main`: This line means the job will only run for commits pushed to the `main` branch. You can adjust this to match your branching strategy, such as including feature branches or tags.

Please note that more complex projects might need to adjust the CMake and make commands with additional arguments, or install more dependencies before building. 

10.  Create a test job for the pipeline. 
To add a test job to the same pipeline, define another job in `.gitlab-ci.yml` , following the `build_application` job. This job should execute after the build job completes successfully, using the artifacts produced by the build for testing purposes. Below is an extension of the previous example, adding in the `test_application` job as well as an updated `stages:` section that has the *build* stage run first and if successful runs the *test* stage.

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
    - apt-get update && apt-get install -y cmake
    - ./build/run_tests # Assume the build process generates an executable named run_tests
  dependencies:
    - build_application
  only:
    - main
```

Here are the key points for the `test_application` job:

- `stage: test`: This places the job in the `test` stage, which runs after the `build` stage as defined in the `stages` section.

- `script:`: The commands in this section are for running your tests. The example assumes there's an executable named `run_tests` that was generated during the build process and is located in the `build` directory. The actual command you use here will depend on how your testing is set up (for instance, you might be using a testing framework like Google Test).

- `dependencies: - build_application`: This line specifies that the `test_application` job depends on the `build_application` job. This makes the artifacts from `build_application` (the `build/` directory) available for the `test_application` job. If your testing does not require any artifacts from the build stage, you could omit this.

- `only: - main`: Similar to the build job, this specifies that the job should only run for the `main` branch.

This setup assumes that the testing executable or script is generated as part of the build process and that it's located in the `build` directory. Modify the `./run_tests` command based on the project's specific setup, including changing the command or installing additional dependencies required for testing.