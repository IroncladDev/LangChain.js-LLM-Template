# Secrets and Environment Variables

Sensitive information, such as credentials and API keys, must be kept secure. Keeping this information separate from your code helps to protect it from unauthorized access when you share your code with others.

A common solution to give your application access to sensitive information is through the use of environment variables. By storing the information as key-value pairs in an environment variable, you can access it in your backend code. On Replit, you can add environment variables and access them using secrets.

It's important to note that while users who clone your Repl will have access to the code, they must set their own values for the environment variables. This helps to maintain the security of sensitive information.

![the secrets icon](https://replit-docs-images.util.repl.co/images/animations/show-secrets.gif)

## How to Add, View, and Edit Environment Variables (Secrets)

To add an environment variable, fill in the information and hit **Add new secret**.

![adding a secret](https://replit-docs-images.util.repl.co/images/animations/add-secret.gif)

You can view or edit any previously saved variable by clicking on its name. The values are usually sensitive and are not shown by default.

![secrets tab with secret](https://replit-docs-images.util.repl.co/images/animations/edit-secret.gif)

## How to Use Environment Variables in Your Code

To use environment variables in your code, follow the code examples provided in the Secrets panel based on your programming language. Here are examples in Python and JavaScript, assuming you have set environment variables with `DB_USERNAME` -> `admin` and `TOKEN` -> `38zdJSDF48fKJSD4824fN`, respectively:

![using a secret in code](https://replit-docs-images.util.repl.co/images/animations/use-secret.gif)

### Python

```python
import os
print(os.getenv("MY_SECRET"))
```

### JavaScript

```javascript
console.log(process.env.MY_SECRET);
```

**Note:** You cannot set environment variables for Repls with only a frontend, such as HTML Repls.
**Note:** To access environment variables set through the UI in the Shell of your Repl (e.g., with `echo $MY_VARIABLE`), you must reboot the Repl by running `kill 1` in the shell.
