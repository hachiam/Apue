# 关于阻止僵尸进程
8-5采用使用两次fork()的方式。
首先，主进程fork()成为第一个子进程的父进程,然后在主进程中调用waitpid()等待子进程终止。
然后，在子进程中调用fork()创建一个孙子进程，然后当子进程终止时，主进程替他释放资源。这时，孙子进程失去了父进程，被init进程捕获。
孙子进程和主进程实现并架崎岖，即使主进程退出，也有init替孙子进程释放资源。所以就避免了僵尸进程。
