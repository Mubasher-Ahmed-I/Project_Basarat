<!-- Project Basarat README - Touch-Activated, AI-Powered Smart Glasses Edition -->

<p align="center">
  <img src="https://img.shields.io/badge/Smart%20Glasses-Visually%20Impaired-blueviolet?style=for-the-badge&logo=eyeem" alt="Project Basarat Banner" />
</p>

<h1 align="center">🦾 Project Basarat</h1>

<p align="center">
  <b>Smart Glasses for Visually Impaired Individuals</b><br>
  <i>Empowerment, autonomy, and safety—driven by next-gen AI.</i>
</p>

---

## 🌟 Vision

**Project Basarat** delivers a next-generation wearable assistive device, using state-of-the-art vision-language models (VLMs) like Gemini, to provide real-time help to visually impaired users. Our mission: make navigation, reading, and independence accessible to everyone.

---

## 🖼️ Gallery

<p align="center">
  <img src="https://github.com/Mubasher-Ahmed-I/Project_Basarat/blob/main/Images/img1.jpg" alt="Device Front View" width="37%"/>
  <img src="https://github.com/Mubasher-Ahmed-I/Project_Basarat/blob/main/Images/img2.jpg" alt="Device Side View" width="37%"/>
</p>
<p align="center">
  <img src="https://github.com/Mubasher-Ahmed-I/Project_Basarat/blob/main/Images/img3.jpg" alt="Device in Action" width="37%"/>
  <img src="https://github.com/Mubasher-Ahmed-I/Project_Basarat/blob/main/Images/Wiring.jpeg" alt="Wiring Diagram" width="37%"/>
</p>

---

## 🔥 Features

- **🎯 Touch-Activated Image Capture:** A single tactile sensor allows the user to take a picture at any moment—no voice or console interaction needed.
- **🦾 AI-Powered Scene Understanding:** Captured images are processed by a Vision-Language Model (e.g., Gemini) to describe the scene, identify obstacles, and read out text.
- **🔊 Real-Time Audio Feedback:** All information is delivered to the user through clear, context-aware audio—no microphone or spoken input required.
- **🔋 Lightweight and Efficient:** Optimized for embedded hardware, maximizing battery life and reliability.

---

## ⚡ Workflow & Logic

<p align="center">
  <img src="https://github.com/Mubasher-Ahmed-I/Project_Basarat/blob/main/Workflow.png" alt="Workflow" width="80%" />
</p>

The interaction flow is simple and accessible:
1. **User presses the touch sensor** to trigger an image capture.
2. **The camera captures the scene** and sends it to a Vision-Language Model (VLM) like Gemini.
3. **The VLM analyzes the image** for obstacles, text, and scene context.
4. **Audio output provides real-time spoken feedback** to the user—no further action needed.

<p align="center">
  <img src="https://github.com/Mubasher-Ahmed-I/Project_Basarat/blob/main/Working_FlowChart.png" alt="Working Flow Chart" width="65%" />
</p>

---

## 🚀 Get Started

### Requirements

- C++17 compiler
- Camera module
- Touch sensor (for image capture)
- Audio output device (speaker or bone conduction transducer)
- Access/API for a Vision-Language Model (VLM) such as Gemini (Google) or equivalent

### Installation

```bash
git clone https://github.com/Mubasher-Ahmed-I/Project_Basarat.git
cd Project_Basarat
# Follow the setup instructions for your VLM integration here
make
```

### Running

```bash
./bin/smart_glasses
```
After powering on, simply press the touch sensor to capture a scene. The system will analyze the image and provide audio feedback.  
No microphone, console, or other input methods are needed—just a simple touch to interact.

---

## 🗂️ Project Structure

```text
Project_Basarat/
├── ESP_CAM_Code/             # Camera firmware/code
├── Images/                   # Device & wiring visuals
│   ├── img1.jpg
│   ├── img2.jpg
│   ├── img3.jpg
│   └── Wiring.jpeg
├── Test_Images/              # Test samples
├── Workflow.png              # Overall workflow diagram
├── Working_FlowChart.png     # Detailed logic flowchart
├── Proposal.pdf              # Project proposal
├── Basarat-Presentation.pptx # Presentation slides
└── README.md                 # This file!
```

---

## ✍️ Dive Deeper

Want to know more about the story, technical journey, and impact of Project Basarat?  
Check out the detailed write-up and other innovative projects on my [personal portfolio](https://portfolio-mubasher.vercel.app/#projects)!  
Read the blog and explore articles for a behind-the-scenes look and implementation insights.

---

## 🤝 Contribute

We welcome contributors! If you have ideas or want to fix bugs, open an issue or submit a pull request.

---


<p align="center">
  <b>Enabling independence, one innovation at a time.</b>
</p>
