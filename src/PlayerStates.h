//#ifndef PLAYER_STATES_H
//#define PLYAER_STATES_H
//#include "player.h"
//class PlayerState {
//public:
//	//virtual allows for future classes to overwrite pre-existing functions
//	//~ is a destructor, and is used when
//	virtual ~PlayerState() = default;
//	virtual void HandleCommand(Player& player, CommandType cmd) = 0;
//	virtual void Enter(Player& player) = 0;
//	virtual void Exit(Player& player) = 0;
//	virtual void Update(Player& player, float& deltaTime) = 0;
//private:
//};
//
//class StandingState : public PlayerState {
//public:
//	static StandingState& Instance() {
//		static StandingState Instance;
//		return Instance;
//	}
//	void Enter(Player& player) override {
//		player.velocity = glm::vec3(0.f);
//	}
//	void Exit(Player& player) override {
//		std::cout << "Player leaves Standing State\n";
//	}
//	void HandleCommand(Player& player, CommandType cmd) override {
//		std::cout << "enters Standing State\n";
//
//		/*if (cmd == CommandType::JumpUp) {
//			player.velocity.y = 6.0f;
//			player.onGround = false;
//			player.SetState(JumpingState::Instance());
//		}
//		else if (cmd == CommandType::MoveForward) {
//			player.SetState(ForwardState::Instance());
//		}*/
//	}
//	void Update(Player& player, float& deltaTime) override {
//		player.velocity = glm::vec3(0.f);
//		player.onGround = true;
//
//	}
//private:
//	StandingState() = default;
//};
//class ForwardState : public PlayerState {
//public:
//	static ForwardState& Instance() {
//		static ForwardState Instance;
//		return Instance;
//	}
//	void Enter(Player& player) override {
//		player.velocity = glm::vec3(0.f);
//	}
//	void Exit(Player& player) override {
//		std::cout << "Player leaves Forward State\n";
//	}
//	void HandleCommand(Player& player, CommandType cmd) override {
//		std::cout << "Forward State\n";
//
//		/*if (cmd == CommandType::JumpUp) {
//			player.velocity.y = 6.0f;
//			player.onGround = false;
//			player.SetState(JumpingState::Instance());
//		}
//		else if (cmd == CommandType::MoveForward) {
//			player.SetState(ForwardState::Instance());
//		}*/
//	}
//	void Update(Player& player, float& deltaTime) override {
//		player.velocity = glm::vec3(0.f);
//		player.onGround = true;
//
//	}
//private:
//	ForwardState() = default;
//};
////----------
//class JumpingState : public PlayerState {
//public:
//	static JumpingState& Instance() {
//		static JumpingState instance;
//		return instance;
//	}
//	void Enter(Player& player) override {
//		player.velocity = glm::vec3(0.f);
//	}
//	void Exit(Player& player) override {
//		std::cout << "Player leaves Jumping State\n";
//	}
//	void HandleCommand(Player& player, CommandType cmd) override{
//		std::cout << "Enter Jump State\n";
//		//if (cmd == CommandType::Jump) {
//		//	player.velocity.y = 6.0f;
//		//	player.onGround = false;
//		//	player.setState(JumpingState::Instance());
//		//}
//	}
//	void Update(Player& player, float& deltaTime) override {
//		player.velocity.y += gravity * deltaTime;
//		player.position += player.velocity * deltaTime;
//
//		if (player.position.y <= player.getGroundHeightAt(player.position.x, player.position.z)) {
//			player.position.y = player.getGroundHeightAt(player.position.x, player.position.z);
//			player.velocity.y = 0;
//			bool onGround = false;
//			player.SetState(StandingState::Instance());  // Transition back to Standing
//		}
//	}
//private:
//	JumpingState() = default;
//};
//
//class BackwardState : public PlayerState {
//public:
//	static BackwardState& Instance() {
//		static BackwardState instance;
//		return instance;
//	}
//	void Enter(Player& player) override {
//		player.velocity = glm::vec3(0.f);
//	}
//	void Exit(Player& player) override {
//		std::cout << "Player leaves Jumping State\n";
//	}
//	void HandleCommand(Player& player, CommandType cmd) override {
//		player.velocity = glm::vec3(5.f);
//		player.onGround = true;
//	}
//	void Update(Player& player, float& deltaTime) override {
//		player.velocity.y += gravity * deltaTime;
//		player.position += player.velocity * deltaTime;
//
//		if (player.position.y <= player.getGroundHeightAt(player.position.x, player.position.z)) {
//			player.position.y = player.getGroundHeightAt(player.position.x, player.position.z);
//			player.velocity.y = 0;
//			bool onGround = false;
//			player.SetState(BackwardState::Instance());  // Transition back to Standing
//		}
//	}
//private:
//	BackwardState() = default;
//};
//#endif
