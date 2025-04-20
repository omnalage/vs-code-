# Use the official nginx image as the base image
FROM nginx:latest

# Copy the index.html file to the default nginx html directory
COPY index.html /usr/share/nginx/html/index.html

# Expose port 8080 for the container
EXPOSE 8080

# Command to start nginx
CMD ["nginx", "-g", "daemon off;"]

