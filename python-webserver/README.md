# Contenedor 2 — Servidor web en Python

## Descripción

Servidor HTTP escrito en Python (stdlib pura, sin dependencias externas) que sirve una página web con información del sistema en tiempo real: versión de Python, hostname del contenedor, PID y hora UTC.

Esta propuesta demuestra un caso de uso completamente diferente al contenedor C: en lugar de generar un archivo, **expone un servicio de red** que puede recibir peticiones HTTP.

## Estructura

```
python-webserver/
├── Dockerfile    # imagen basada en python:3.12-alpine
└── app.py        # servidor HTTP con visualización de sistema info
```

## Cómo funciona el Dockerfile

```dockerfile
FROM python:3.12-alpine    # imagen base ultra-ligera (~50 MB)

WORKDIR /app

COPY app.py .

EXPOSE 8080                # declara el puerto que usa la aplicación

CMD ["python", "app.py"]   # arrancar el servidor al ejecutar el contenedor
```

## Pasos para construir y ejecutar

### 1. Construir la imagen

```bash
docker build -t python-webserver .
```

### 2. Ejecutar el contenedor

```bash
docker run --rm -p 8080:8080 python-webserver
```

**Explicación de las flags:**
- `--rm` — elimina el contenedor al pararlo
- `-p 8080:8080` — mapea el puerto 8080 del host al puerto 8080 del contenedor

### 3. Verificar el resultado

Abre el navegador en **http://localhost:8080** y verás la página con la información del sistema.

O desde la terminal:

```bash
curl http://localhost:8080
```

### 4. Detener el contenedor

Presiona `Ctrl+C` en la terminal donde corre, o desde otra terminal:

```bash
docker stop $(docker ps -q --filter ancestor=python-webserver)
```

## Salida esperada en la terminal

```
Serving on http://0.0.0.0:8080
[2026-05-03T20:00:00.000000] "GET / HTTP/1.1" 200 -
```

## Diferencias con el Contenedor 1

| Aspecto | Contenedor C | Contenedor Python |
|---------|-------------|-------------------|
| Lenguaje | C | Python 3.12 |
| Imagen base | debian:bookworm-slim | python:3.12-alpine |
| Dependencias | gcc, libjpeg | ninguna (stdlib) |
| Resultado | archivo JPG | servicio HTTP activo |
| Puerto | — | 8080 |
| Interacción | una sola ejecución | continua, vía browser/curl |
