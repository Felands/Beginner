class PlayerCreator : public BaseCreator
{
 GameObject* createGameObject() const
 {
 return new Player();
 }
};