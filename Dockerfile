FROM alpine
LABEL authors="Lobato"

RUN apk add cmake make gcc g++ git

# Installing google test
RUN git clone https://github.com/google/benchmark.git
RUN cd benchmark
RUN cmake -E make_directory "benchmark/build"
RUN cmake -E chdir "benchmark/build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=Release ../
RUN cmake --build "benchmark/build" --config Release
RUN cmake --build "benchmark/build" --config Release --target install

WORKDIR /AOC

COPY . .

ARG DAY=1
ARG PART1=0
ARG PART2=0

ENV EXE_NAME=Day_${DAY}
ENV EXE_PATH="/AOC/build/src/AOC 2023/Day ${DAY}"

RUN cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DBENCHMARK_ONLY=1 -DPART1=${PART1} -DPART2=${PART2} -B build .

RUN make -C build Day_${DAY}

RUN cp "$EXE_PATH/$EXE_NAME"  /AOC/solution
RUN cp "$EXE_PATH/input.txt" /AOC

ENTRYPOINT ["./solution"]