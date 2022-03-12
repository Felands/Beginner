struct Tileset
{
 int firstGridID;
 int tileWidth;
 int tileHeight;
 int spacing;
 int margin;
 int width;
 int height;
 int numColumns;
 std::string name;
};

class Level
{
 public:
 Level();
 ~Level() {}
 void update();
 void render();

std::vector<Tileset>* getTilesets() 
{ 
 return &m_tilesets; 
}
Player* getPlayer() { return m_pPlayer; }
void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:
 friend class LevelParser;
 Level();

 private:
 std::vector<Tileset> m_tilesets;
 Player* m_pPlayer;

};