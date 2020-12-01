projectpath="/mnt/d/Academics/pinot/build/bin/designPatterns"
projectname="designPatterns"
find ${projectpath} -name '*.java' > ${projectname}-files.list
pinot @${projectname}-files.list
