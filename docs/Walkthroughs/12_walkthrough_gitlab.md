# Extended GitLab Sample
## Sample Pipeline
Here is a longer example of a `.gitlab-ci.yml` file.

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