//#include "player.h"
//#include "PlayerStates.h"
//#include "Model.h"
//#include "shaderClass.h"
//
//const float SENSE = 0.1f;
//const float YAW_P = -90.0f;
//const float PITCH_P = 0.0f;
//const float gravity = -9.8f;
//
//Player::Player(const std::string& modelPath, glm::vec3 pos, glm::vec3 vel, glm::vec3 up, float yaw, float pitch)
//    : model(modelPath), position(pos), Front(0, 0, -1),
//    speed(5.0f), Yaw(YAW_P), Pitch(PITCH_P),
//    MouseSensitivity(SENSE), velocity(0.0f),
//    WorldUp(0.0f, 1.0f, 0.0f), onGround(true),
//    currentState(nullptr) 
//{ 
//    updatePlayerVectors();
//    SetState(StandingState::Instance()); 
//}
//
//void Player::SetState(PlayerState& newState) {
//    if (currentState) currentState->Exit(*this);
//    currentState = &newState;
//    currentState->Enter(*this);
//    onGround = (dynamic_cast<JumpingState*>(currentState) == nullptr);
//}
//
//void Player::Update(float& deltaTime) {
//    if (currentState) currentState->Update(*this, deltaTime);
//}
//
//void Player::HandleCommand(CommandType cmd) {
//    if (currentState) currentState->HandleCommand(*this, cmd);
//}
//
//glm::vec3 Player::getPlayerPos() const { return position; }
//
//void Player::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
//    xoffset *= MouseSensitivity;
//    yoffset *= MouseSensitivity;
//
//    Yaw += xoffset;
//    Pitch += yoffset;
//
//    if (constrainPitch) {
//        Pitch = glm::clamp(Pitch, -89.0f, 89.0f);
//    }
//
//    updatePlayerVectors();
//}
//
//float Player::getGroundHeightAt(float x, float z) {
//    return 0.0f; // flat terrain
//}
//
//void Player::Draw(Shader& shader) {
//    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
//    shader.setMat4("model", modelMatrix);
//    model.Draw(shader); 
//}
// 
//void Player::updatePlayerVectors() {
//    glm::vec3 front;
//    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//    front.y = sin(glm::radians(Pitch));
//    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//    Front = glm::normalize(front);
//    Right = glm::normalize(glm::cross(Front, WorldUp));
//    Up = glm::normalize(glm::cross(Right, Front));
//}