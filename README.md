# Docker Activity

Este repositorio contiene dos contenedores Docker desarrollados como parte de la actividad de aprendizaje sobre Docker.

## Contenido

```
docker-activity/
├── c-image-generator/     # Contenedor 1: programa en C que genera un JPG
│   ├── Dockerfile
│   ├── generate_image.c
│   └── README.md
├── python-webserver/      # Contenedor 2: servidor web en Python
│   ├── Dockerfile
│   ├── app.py
│   └── README.md
├── .gitignore
└── README.md              ← este archivo
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

Consulta [`c-image-generator/README.md`](c-image-generator/README.md) para la guía completa.

**Resumen rápido:**

```bash
# Construir
docker build -t c-image-generator ./c-image-generator

# Ejecutar y obtener el JPG en el directorio actual
docker run --rm -v "$(pwd)/output:/app" c-image-generator
```

El archivo `output.jpg` aparecerá en la carpeta `output/`.

---

## Contenedor 2 — Servidor web en Python

Consulta [`python-webserver/README.md`](python-webserver/README.md) para la guía completa.

**Resumen rápido:**

```bash
# Construir
docker build -t python-webserver ./python-webserver

# Ejecutar (disponible en http://localhost:8080)
docker run --rm -p 8080:8080 python-webserver
```

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
