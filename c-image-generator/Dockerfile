FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends gcc libjpeg-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /build

COPY generate_image.c .

RUN gcc -O2 -o /usr/local/bin/generate_image generate_image.c -ljpeg

WORKDIR /output

CMD ["generate_image"]
