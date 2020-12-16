projectpath="/mnt/d/Academics/pinot/build/bin/designPatterns"
projectname="designPatterns"
find ${projectpath} -name '*.java' > ${projectname}-files.list
/mnt/d/Academics/SEaM/SoftwareEvolutionPinot/pinot/build/bin/pinot @${projectname}-files.list
