# Docker 

Este repositorio contiene dos contenedores Docker desarrollados como parte de la actividad de aprendizaje sobre Docker.

## Contenido

```
docker-activity/
├── c-image-generator/
│   ├── Dockerfile
│   └── generate_image.c
├── python-webserver/
│   ├── Dockerfile
│   └── app.py
├── evidencia/
│   ├── c-output.jpg
│   └── dockerweb.png
├── .gitignore
└── README.md
```

---

## Entorno utilizado

Este proyecto se desarrolló en **Linux (Ubuntu)** usando **Docker Engine CLI** en lugar de Docker Desktop.

### ¿Por qué Docker Engine CLI y no Docker Desktop?

Docker Desktop es una aplicación con interfaz gráfica disponible principalmente para Windows y macOS. En Linux, Docker Desktop existe pero es opcional y requiere instalación adicional; la forma nativa y estándar de usar Docker es directamente mediante el **Docker Engine**, que se instala como servicio del sistema y se controla desde la terminal.

| | Docker Desktop | Docker Engine CLI |
|---|---|---|
| Interfaz | Gráfica (GUI) | Terminal |
| Disponibilidad en Linux | Opcional | Nativa |
| Rendimiento | Capa de virtualización extra en Win/Mac | Corre directamente sobre el kernel |
| Uso típico | Desarrollo en Windows/macOS | Servidores y Linux en general |

En Linux, el motor de Docker corre directamente sobre el **kernel** del sistema operativo gracias a los namespaces y cgroups, sin necesidad de una máquina virtual intermedia. Esto lo hace más eficiente y es la opción preferida en entornos de producción y servidores.

```bash
docker --version
# Docker version 29.4.2, build 055a478
```

---

## ¿Qué es Docker?

Docker es una plataforma de **contenedores de software**. Un contenedor empaqueta el código de una aplicación junto con todas sus dependencias (librerías, configuración, sistema operativo base) en una unidad portable e independiente.

### Conceptos clave

| Concepto | Descripción |
|----------|-------------|
| **Imagen** | Plantilla de solo lectura que define el contenedor (como una "receta"). Se construye con `docker build`. |
| **Contenedor** | Instancia en ejecución de una imagen. Se lanza con `docker run`. |
| **Dockerfile** | Archivo de texto con las instrucciones para construir una imagen. |
| **Registro** | Repositorio de imágenes (ej. Docker Hub). |

### Flujo básico

```
Dockerfile  →  docker build  →  Imagen  →  docker run  →  Contenedor
```

---

## Contenedor 1 — Generador de imagen JPG en C

Programa en C que genera una imagen JPG de **800×600 px** usando la librería `libjpeg`. La imagen contiene un gradiente de fondo y cuatro rectángulos de colores.

### Cómo funciona el Dockerfile

```dockerfile
FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y gcc libjpeg-dev

WORKDIR /build
COPY generate_image.c .
RUN gcc -O2 -o /usr/local/bin/generate_image generate_image.c -ljpeg

WORKDIR /output
CMD ["generate_image"]
```

- La imagen base es Debian mínimo.
- Se instalan `gcc` y `libjpeg-dev` para compilar.
- El binario se instala en `/usr/local/bin/` para que el volumen de salida no lo sobreescriba.
- El contenedor trabaja en `/output`, que se monta desde el host.

### El programa en C

`generate_image.c` realiza los siguientes pasos:

1. Reserva memoria para una imagen RGB de 800×600 píxeles.
2. Pinta un gradiente de fondo (rojo = eje X, verde = eje Y).
3. Dibuja cuatro rectángulos de colores sólidos.
4. Usa la API de `libjpeg` para comprimir y escribir `output.jpg` con calidad 90%.
5. Libera la memoria y cierra el archivo.

### Construir y ejecutar

```bash
docker build -t c-image-generator ./c-image-generator
mkdir -p output
docker run --rm -v "$(pwd)/output:/output" c-image-generator
```

- `--rm` — elimina el contenedor al terminar
- `-v "$(pwd)/output:/output"` — monta la carpeta local para recibir el JPG generado

Salida esperada:
```
Generated output.jpg (800x600, 90% quality)
```

---

## Contenedor 2 — Servidor web en Python

Servidor HTTP escrito en Python (stdlib pura, sin dependencias externas) que expone una página web con información del sistema en tiempo real: versión de Python, hostname del contenedor, PID y hora UTC.

A diferencia del contenedor C, este no genera un archivo sino que **expone un servicio de red** que responde peticiones HTTP de forma continua.

### Cómo funciona el Dockerfile

```dockerfile
FROM python:3.12-alpine

WORKDIR /app
COPY app.py .

EXPOSE 8080
CMD ["python", "app.py"]
```

- La imagen base `python:3.12-alpine` pesa ~50 MB (mucho más ligera que Debian).
- No requiere dependencias externas, usa solo la stdlib de Python.
- Expone el puerto 8080.

### Construir y ejecutar

```bash
docker build -t python-webserver ./python-webserver
docker run --rm -p 8080:8080 python-webserver
```

- `--rm` — elimina el contenedor al pararlo
- `-p 8080:8080` — mapea el puerto 8080 del host al 8080 del contenedor

Luego abrir **http://localhost:8080** en el navegador. Para detener: `Ctrl+C`.

Salida esperada en terminal:
```
Serving on http://0.0.0.0:8080
[2026-05-04T02:05:38] "GET / HTTP/1.1" 200 -
```

### Comparación entre contenedores

| Aspecto | Contenedor C | Contenedor Python |
|---------|-------------|-------------------|
| Lenguaje | C | Python 3.12 |
| Imagen base | debian:bookworm-slim | python:3.12-alpine |
| Dependencias | gcc, libjpeg | ninguna (stdlib) |
| Resultado | archivo JPG | servicio HTTP activo |
| Puerto | — | 8080 |
| Interacción | una sola ejecución | continua, vía browser/curl |

---

## Comandos Docker de referencia

```bash
docker images                    # listar imágenes locales
docker ps                        # contenedores en ejecución
docker ps -a                     # todos los contenedores
docker stop <id>                 # detener contenedor
docker rm <id>                   # eliminar contenedor
docker rmi <nombre>              # eliminar imagen
docker logs <id>                 # ver logs del contenedor
```
