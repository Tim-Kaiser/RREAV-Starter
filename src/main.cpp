#include "../include/rreav_includes.h"
#include "SFML/System/Clock.hpp"

#define chunkSize 2048

int main() {
  //===== INIT =====
  Interface interface;
  ShaderManager shaderManager;
  AudioManager audioManager("resources/audio/sine_wave_1000hz_44.1sr.wav",
                            chunkSize, 0);

  std::unique_ptr<Shader> renderShader = shaderManager.CreateShaders(
      "resources/shaders/main.vert", "resources/shaders/main.frag");
  glUseProgram(renderShader->m_shaderProgramID);

  Mesh mesh = loadObject("resources/objects/quad.obj");

  // audioManager.setVolume(0.02);
  // audioManager.play();
  audioManager.bindAudioBuffer();

  sf::Clock clock;
  while (interface.running()) {
    int time = clock.getElapsedTime().asMilliseconds();
    shaderManager.SendUniformData("u_time", time);
    audioManager.update();

    mesh.render();
    interface.update();
    interface.draw();
  }

  return 0;
}
