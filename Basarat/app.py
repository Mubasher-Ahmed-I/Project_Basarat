from flask import Flask, request, jsonify
import cv2
import numpy as np
from io import BytesIO
from PIL import Image
import easyocr

app = Flask(__name__)
reader = easyocr.Reader(['en'])




@app.route('/')
def home():
    return "<h1>Hello OCR</h1>"

@app.route('/process-image', methods=['POST'])
def process_image():
    # Check if an image was uploaded
    if 'image' not in request.files:
        return jsonify({"error": "No image file provided"}), 400

    image = request.files['image']

    # Convert the uploaded image to a format that OpenCV can work with
    try:
        # Read the image using PIL, then convert to a numpy array
        pil_image = Image.open(image)
        img = np.array(pil_image)

        # Convert the image from RGB to BGR (OpenCV uses BGR)
        img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)

        # Use easyocr to process the image
        results = reader.readtext(
            img,
            decoder='greedy',
            beamWidth=5,
            batch_size=10,
            workers=0,
            allowlist=None,
            blocklist=None,
            detail=1,
            rotation_info=None,
            paragraph=False,
            min_size=20,
            contrast_ths=0.01,
            adjust_contrast=0.09,
            filter_ths=0.003,
            text_threshold=0.6,
            low_text=0.4,
            link_threshold=0.4,
            canvas_size=2560,
            mag_ratio=2.4,
            slope_ths=0.1,
            ycenter_ths=0.5,
            height_ths=0.5,
            width_ths=0.5,
            y_ths=0.5,
            x_ths=1.0,
            add_margin=0.1,
            threshold=0.2,
            bbox_min_score=0.2,
            bbox_min_size=3,
            max_candidates=0,
            output_format='standard'
        )

        # Extract the text from the OCR results
        extracted_text = []
        for (bbox, text, confidence) in results:
            extracted_text.append(str(text))

        return jsonify({"text": extracted_text})

       # return jsonify({"text": results})

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == "__main__":
    app.run()
