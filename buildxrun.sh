cmake -S . -B build &&
cd build &&
make &&
./autogit $1 $2 $3 $4 $5 $6
