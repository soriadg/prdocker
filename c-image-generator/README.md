# Contenedor 1 — Generador de imagen JPG en C

## Descripción

Programa en C que genera una imagen JPG de **800×600 px** usando la librería `libjpeg`. La imagen contiene un gradiente de fondo y rectángulos de colores.

## Estructura

```
c-image-generator/
├── Dockerfile          # instrucciones para construir la imagen Docker
└── generate_image.c    # código fuente en C
```

## Cómo funciona el Dockerfile

```dockerfile
FROM debian:bookworm-slim          # imagen base: Debian mínimo

RUN apt-get update && \
    apt-get install -y gcc libjpeg-dev   # instalar compilador y librería JPEG

WORKDIR /app                       # directorio de trabajo dentro del contenedor

COPY generate_image.c .            # copiar el código fuente

RUN gcc -O2 -o generate_image generate_image.c -ljpeg  # compilar

CMD ["./generate_image"]           # comando por defecto al ejecutar
```

## Pasos para construir y ejecutar

### 1. Construir la imagen

```bash
docker build -t c-image-generator .
```

**¿Qué hace este comando?**
- `docker build` — construye una imagen Docker
- `-t c-image-generator` — le asigna el nombre `c-image-generator`
- `.` — usa el Dockerfile del directorio actual

### 2. Ejecutar el contenedor

```bash
mkdir -p output
docker run --rm -v "$(pwd)/output:/app" c-image-generator
```

**Explicación de las flags:**
- `--rm` — elimina el contenedor automáticamente al terminar
- `-v "$(pwd)/output:/app"` — monta la carpeta local `output/` en `/app` dentro del contenedor, para que el JPG generado sea accesible desde el host

### 3. Verificar el resultado

```bash
ls -lh output/output.jpg
```

Deberías ver el archivo `output.jpg` de aproximadamente 50–80 KB.

## Salida esperada

```
Generated output.jpg (800x600, 90% quality)
```

## El programa en C

El programa (`generate_image.c`) realiza los siguientes pasos:

1. Reserva memoria para una imagen RGB de 800×600 píxeles.
2. Pinta un gradiente de fondo (rojo = eje X, verde = eje Y).
3. Dibuja cuatro rectángulos de colores sólidos.
4. Usa la API de `libjpeg` para comprimir y escribir el archivo `output.jpg` con calidad 90%.
5. Libera la memoria y cierra el archivo.
