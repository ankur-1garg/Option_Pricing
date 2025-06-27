# --- Stage 1: The Builder ---
# This stage compiles the application. It contains the C++ toolchain.
FROM ubuntu:22.04 AS builder

# Set the working directory inside the container
WORKDIR /app

# Install the necessary build tools
RUN apt-get update && apt-get install -y build-essential cmake

# Copy the entire project source code into the container's /app directory
COPY . .

# Run the CMake build process
RUN cmake -B build && cmake --build build


# --- Stage 2: The Final Image ---
# This stage creates the final, lightweight image. It does NOT contain the C++ toolchain.
FROM ubuntu:22.04

# Set the working directory
WORKDIR /app

# Copy ONLY the compiled executable from the 'builder' stage
COPY --from=builder /app/build/demo .

# Set the default command to run when the container starts.
# This will execute our interactive demo.
CMD ["./demo"]
