projectpath="./designPatterns"
projectname="designPatterns"
find ${projectpath} -name '*.java' > ${projectname}-files.list
./pinot @${projectname}-files.list
