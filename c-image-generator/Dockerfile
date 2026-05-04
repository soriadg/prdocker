FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends gcc libjpeg-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY generate_image.c .

RUN gcc -O2 -o generate_image generate_image.c -ljpeg

CMD ["./generate_image"]
