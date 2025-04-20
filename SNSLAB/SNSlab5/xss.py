from flask import Flask, request, render_template_string
from markupsafe import escape as markup_escape

app = Flask(__name__)

# Secure template with proper styling and XSS protection
TEMPLATE = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>XSS Demo</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            line-height: 1.6;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        
        .container {
            background-color: white;
            padding: 2rem;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
        }
        
        h1 {
            color: #2c3e50;
            margin-bottom: 1.5rem;
        }
        
        .form-group {
            margin-bottom: 1rem;
        }
        
        label {
            display: block;
            margin-bottom: 0.5rem;
            color: #34495e;
        }
        
        input[type="text"] {
            width: 100%;
            padding: 8px;
            border: 1px solid #ddd;
            border-radius: 4px;
            font-size: 16px;
            margin-bottom: 1rem;
        }
        
        button {
            background-color: #3498db;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
            transition: background-color 0.3s;
        }
        
        button:hover {
            background-color: #2980b9;
        }
        
        .back-link {
            display: inline-block;
            margin-top: 1rem;
            color: #3498db;
            text-decoration: none;
        }
        
        .back-link:hover {
            text-decoration: underline;
        }
        
        .message {
            padding: 1rem;
            background-color: #f8f9fa;
            border-radius: 4px;
            margin-bottom: 1rem;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Welcome</h1>
        <form method="POST">
            <div class="form-group">
                <label for="name">Please enter your name:</label>
                <input type="text" id="name" name="name" required>
            </div>
            <button type="submit">Submit</button>
        </form>
    </div>
</body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def input_demo():
    if request.method == "POST":
        name = request.form.get("name")
        return render_template_string(f"""
            <!DOCTYPE html>
            <html>
            <head>
                <title>XSS Demo</title>
                <style>
                    body {{
                        font-family: 'Arial', sans-serif;
                        line-height: 1.6;
                        max-width: 800px;
                        margin: 0 auto;
                        padding: 20px;
                        background-color: #f5f5f5;
                    }}
                    .back-link {{
                        display: inline-block;
                        margin-top: 1rem;
                        color: #3498db;
                        text-decoration: none;
                    }}
                    .back-link:hover {{
                        text-decoration: underline;
                    }}
                    .h1 {{
                        color: #2c3e50;
                        margin-bottom: 1.5rem;
                    }}
                </style>
            </head>
            <body>
                <h1>Hello, {name}</h1>
                <a href="/" class="back-link">← Go back</a>
            </body>
            </html>
        """)
    return render_template_string(TEMPLATE)

if __name__ == "__main__":
    app.run(debug=True)