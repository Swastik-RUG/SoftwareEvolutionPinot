projectpath="./design-patterns-spring-boot-master"
projectname="design-patterns-spring-boot-master"
find ${projectpath} -name '*.java' > ${projectname}-files.list
./pinot @${projectname}-files.list
