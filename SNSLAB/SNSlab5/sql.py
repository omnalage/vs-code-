import sqlite3
from flask import Flask, request, render_template_string

app = Flask(__name__)

# Initialize the database with more user details
def init_db():
    conn = sqlite3.connect("users.db")
    cursor = conn.cursor()

    cursor.execute("DROP TABLE IF EXISTS users")

    # Create a table with additional columns
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            password TEXT NOT NULL,
            email TEXT NOT NULL,
            role TEXT NOT NULL
        )
    """)

    # Insert sample user data
    cursor.execute("INSERT INTO users (username, password, email, role) VALUES ('admin', 'admin', 'admin@example.com', 'Admin')")
    cursor.execute("INSERT INTO users (username, password, email, role) VALUES ('user', 'user', 'user@example.com', 'User')")
    cursor.execute("INSERT INTO users (username, password, email, role) VALUES ('alice', 'password', 'alice@example.com', 'Editor')")
    cursor.execute("INSERT INTO users (username, password, email, role) VALUES ('bob', 'password', 'bob@example.com', 'Viewer')")
    conn.commit()

    conn.close()

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")

        conn = sqlite3.connect("users.db")
        cursor = conn.cursor()

        # Vulnerable SQL query (demonstration purpose only)
        query = f"SELECT * FROM users WHERE username='{username}' AND password='{password}'"
        print(f"Executed query: {query}")  # Debugging purposes
        users = cursor.execute(query).fetchall()
        conn.close()

        if users:
            # Render fetched users in an HTML table
            user_table = """
            <!DOCTYPE html>
            <html>
            <head>
                <title>Fetched Users</title>
                <style>
                    body {
                        font-family: Arial, sans-serif;
                        margin: 2rem;
                    }
                    table {
                        border-collapse: collapse;
                        width: 100%;
                        margin-top: 20px;
                    }
                    table, th, td {
                        border: 1px solid #ddd;
                    }
                    th, td {
                        padding: 10px;
                        text-align: left;
                    }
                    th {
                        background-color: #f4f4f4;
                    }
                    h1 {
                        color: #2c3e50;
                    }
                </style>
            </head>
            <body>
                <h1>Fetched Users</h1>
                <table>
                    <thead>
                        <tr>
                            <th>ID</th>
                            <th>Username</th>
                            <th>Password</th>
                            <th>Email</th>
                            <th>Role</th>
                        </tr>
                    </thead>
                    <tbody>
            """
            for user in users:
                user_table += f"""
                <tr>
                    <td>{user[0]}</td>
                    <td>{user[1]}</td>
                    <td>{user[2]}</td>
                    <td>{user[3]}</td>
                    <td>{user[4]}</td>
                </tr>
                """
            user_table += """
                    </tbody>
                </table>
                <a href="/">← Go back</a>
            </body>
            </html>
            """
            return user_table
        else:
            return "Invalid username or password."

    # Login form
    return render_template_string("""
        <!DOCTYPE html>
        <html>
        <head>
            <title>SQL Injection</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    margin: 2rem;
                }
                input {
                    padding: 10px;
                    font-size: 16px;
                    border-radius: 4px;
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
            </style>
        </head>
        <body>
            <h1>Login</h1>
            <form method="POST">
                <label for="username">Username:</label>
                <input type="text" id="username" name="username" required><br>
                <label for="password">Password:</label>
                <input type="password" id="password" name="password" required><br>
                <button type="submit">Login</button>
            </form>
        </body>
        </html>
    """)

if __name__ == "__main__":
    init_db()
    app.run(debug=True)

"""
For
Username: ' OR 1=1 --
Password: anything
The query becomes:
SELECT * FROM users WHERE username='' OR 1=1 -- AND password='';
This query will return all users from the database, regardless of the username and password provided.
"""