FROM ubuntu:22.04 AS build
RUN apt-get update && apt-get install -y git build-essential cmake
WORKDIR /app
COPY . .
RUN cmake -S . -B build && cmake --build build

FROM ubuntu:22.04
RUN apt-get update && apt-get install -y python3 python3-pip
RUN pip3 install flask
COPY --from=build /app/build/simulator /simulator
COPY tokens.txt /tokens.txt
COPY stub_server /stub_server
WORKDIR /
EXPOSE 5000
CMD ["/simulator"]

