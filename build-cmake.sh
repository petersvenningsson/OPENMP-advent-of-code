rm -r build
mkdir build
cd build
cmake ..
make

for i in {0..2}
do
    echo "Single-threaded runtime ..."
    OMP_NUM_THREADS=1 hyperfine "./day$i ../data/day$i.txt" 2> /dev/null

    echo "Multi-threaded runtime ..."
    hyperfine "./day$i ../data/day$i.txt" 2> /dev/null
done
