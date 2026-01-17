from flask import Flask, request, jsonify
import subprocess
import os

app = Flask(__name__)

EXECUTABLE_NAME = "explorer_rubik"
EXECUTABLE_PATH = os.path.join(".", EXECUTABLE_NAME)

EXECUTABLE_DIR = "./explorer"

@app.route("/solve", methods=["GET"])
def solve():
    seq = request.args.get("seq")
    if not seq:
        return jsonify({"error": "Missing parameter 'seq'"}), 400

    try:
        result = subprocess.run(
            [EXECUTABLE_PATH, seq],
            capture_output=True,
            text=True,
            timeout=10,
            cwd=EXECUTABLE_DIR  
        )

        return jsonify({
            "input": seq,
            "output": result.stdout.strip(),
            "error": result.stderr.strip()
        })

    except subprocess.TimeoutExpired:
        return jsonify({"error": "Execution timeout"}), 500
    except FileNotFoundError:
        return jsonify({"error": f"Executable not found at {os.path.join(EXECUTABLE_DIR, EXECUTABLE_NAME)}"}), 500
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route("/solveTwo", methods=["GET"])
def solveTwo():
    seq = request.args.get("seq")
    if not seq:
        return jsonify({"error": "Missing parameter 'seq'"}), 400

    try:
        result = subprocess.run(
            [EXECUTABLE_PATH, "-2", seq],  
            capture_output=True,
            text=True,
            timeout=10,
            cwd=EXECUTABLE_DIR
        )

        return jsonify({
            "input": seq,
            "output": result.stdout.strip(),
            "error": result.stderr.strip()
        })

    except subprocess.TimeoutExpired:
        return jsonify({"error": "Execution timeout"}), 500
    except FileNotFoundError:
        return jsonify({"error": f"Executable not found at {os.path.join(EXECUTABLE_DIR, EXECUTABLE_NAME)}"}), 500
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route("/health", methods=["GET"])
def health():
    return jsonify({"status": "ok"})

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)


# async function getRubikSolution(sequence) {
#   try {
    # const encodedSeq = encodeURIComponent(sequence); // asegura que los espacios/apóstrofes funcionen
    # const response = await fetch(`/solve?seq=${encodedSeq}`);
    # const data = await response.json();
# 
    # if (data.error) {
    #   console.error("Error del backend:", data.error);
    #   return null;
    # }
# 
    # return data.output; // La solución
#   } catch (err) {
    # console.error("Error conectando con el backend:", err);
    # return null;
#   }
# }
# 
# // Llama a tu endpoint /solveTwo
# async function getRubikSolutionTwo(sequence) {
#   try {
    # const encodedSeq = encodeURIComponent(sequence);
    # const response = await fetch(`/solveTwo?seq=${encodedSeq}`);
    # const data = await response.json();
# 
    # if (data.error) {
    #   console.error("Error del backend:", data.error);
    #   return null;
    # }
# 
    # return data.output;
#   } catch (err) {
    # console.error("Error conectando con el backend:", err);
    # return null;
#   }
# }