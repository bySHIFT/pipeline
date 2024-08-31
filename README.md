# pipeline
一次 pipeline 其实相当于一次构建任务，里面可以包含多个流程，比如自动构建、自动进行单元测试、自动进行代码检查等流程;

# stages
* stages 表示构建阶段，就是上面提到的流程;
* 可以在一次 pipeline 中定义多个 stage;
* stages有如下特点:
  - 所有 stages 会按照顺序运行，即当一个 stage 完成后，下一个 stage 才会开始
  - 只有当所有 stages 成功完成后，该构建任务 (pipeline) 才算成功
  - 如果任何一个 stage 失败，那么后面的 stages 不会执行，该构建任务 (pipeline) 失败

# jobs
* job表示构建工作，表示某个stage里面执行的工作;
* 一个stage里面可以定义多个job;
* jobs有如下特点:
  - 相同 stage 中的jobs 会并行执行
  - 相同 stage 中的 jobs 都执行成功时，该 stage 才会成功
  - 如果任何一个job 失败，那么该 stage 失败，即该构建任务 (pipeline) 失败
