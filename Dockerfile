FROM alpine
LABEL authors="Lobato"

RUN apk add cmake make gcc g++

WORKDIR /AOC

COPY . .

ARG DAY=1
ARG PART1=0
ARG PART2=0

ENV EXE_NAME=Day_${DAY}
ENV EXE_PATH="/AOC/build/src/AOC 2023/Day ${DAY}"

RUN cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DNO_OUTPUT=1 -DPART1=${PART1} -DPART2=${PART2} -B build .

RUN make -C build Day_${DAY}

RUN cp "$EXE_PATH/$EXE_NAME"  /AOC/solution
RUN cp "$EXE_PATH/input.txt" /AOC

RUN rm -rf CMakeLists.txt build src

CMD echo start && ./solution