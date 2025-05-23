#!/bin/bash


testname=gooduser_basic
BATCHPATH=/home/zsarwar/cs144-aut-23-admin/projects/p4shell/batch-files
OUTPUTPATH=/home/zsarwar/cs144-aut-23-admin/projects/p4shell/expected-output


./clean.sh

mkdir out

../myshell  $BATCHPATH/$testname 1> out/$testname.stdout 2> out/$testname.stderr

echo "Testing $testname stdout"
diff out/$testname.stdout $OUTPUTPATH/$testname.stdout
echo "Testing $testname stderr"
diff out/$testname.stderr $OUTPUTPATH/$testname.stderr

for filename in *_rd_*;do
        if [[ $filename == "*_rd_*" ]]
        then
                exit
        fi
        echo "Testing $filename redirection"
        diff $OUTPUTPATH/$filename $filename
done

exit

# You can put any old command down here,
# or any garbage, it won't be called since we
# already called "exit" above

bla bla (will not be called)
