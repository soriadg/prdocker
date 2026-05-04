from http.server import BaseHTTPRequestHandler, HTTPServer
import platform, datetime, os

PORT = 8080

HTML = """\
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Docker Python Server</title>
  <style>
    body {{ font-family: sans-serif; background: #1e1e2e; color: #cdd6f4;
           display: flex; justify-content: center; align-items: center;
           min-height: 100vh; margin: 0; }}
    .card {{ background: #313244; border-radius: 12px; padding: 2rem 3rem;
             box-shadow: 0 8px 32px #00000066; max-width: 520px; width: 100%; }}
    h1 {{ color: #89b4fa; margin-top: 0; }}
    table {{ width: 100%; border-collapse: collapse; margin-top: 1rem; }}
    td {{ padding: .4rem .6rem; border-bottom: 1px solid #45475a; }}
    td:first-child {{ color: #a6adc8; width: 40%; }}
    .badge {{ display: inline-block; background: #a6e3a1; color: #1e1e2e;
              border-radius: 4px; padding: .1rem .5rem; font-size: .85rem; }}
  </style>
</head>
<body>
  <div class="card">
    <h1>Docker Python Web Server</h1>
    <span class="badge">running</span>
    <table>
      <tr><td>Time (UTC)</td><td>{time}</td></tr>
      <tr><td>Python</td><td>{python}</td></tr>
      <tr><td>Platform</td><td>{platform}</td></tr>
      <tr><td>Hostname</td><td>{hostname}</td></tr>
      <tr><td>PID</td><td>{pid}</td></tr>
    </table>
  </div>
</body>
</html>
"""

class Handler(BaseHTTPRequestHandler):
    def log_message(self, fmt, *args):
        print(f"[{datetime.datetime.utcnow().isoformat()}] {fmt % args}")

    def do_GET(self):
        body = HTML.format(
            time=datetime.datetime.utcnow().strftime("%Y-%m-%d %H:%M:%S"),
            python=platform.python_version(),
            platform=platform.system() + " " + platform.machine(),
            hostname=platform.node(),
            pid=os.getpid(),
        ).encode()
        self.send_response(200)
        self.send_header("Content-Type", "text/html; charset=utf-8")
        self.send_header("Content-Length", len(body))
        self.end_headers()
        self.wfile.write(body)

if __name__ == "__main__":
    server = HTTPServer(("", PORT), Handler)
    print(f"Serving on http://0.0.0.0:{PORT}")
    server.serve_forever()
