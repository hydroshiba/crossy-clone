#include "texture_holder.hpp"

TextureHolder::TextureHolder() {
	map["TITLE"] = new Texture("asset/texture/title.bmp");

	map["CREDIT_ASTRAUNAUT"] = new Texture("asset/texture/credit/astraunaut.bmp");
	map["CREDIT_CAT"] = new Texture("asset/texture/credit/cat-temporary.bmp");
	map["CREDIT_FOX"] = new Texture("asset/texture/credit/fox.bmp");
	map["CREDIT_SEAL"] = new Texture("asset/texture/credit/seal.bmp");
	
	map["BGM"] = new Texture("asset/texture/button/bgm.bmp");
	map["BGM_CLICKED"] = new Texture("asset/texture/button/bgm_clicked.bmp");
	map["CONTINUE"] = new Texture("asset/texture/button/continue.bmp");
	map["CONTINUE_CLICKED"] = new Texture("asset/texture/button/continue_clicked.bmp");
	map["CREDIT"] = new Texture("asset/texture/button/credit.bmp");
	map["CREDIT_CLICKED"] = new Texture("asset/texture/button/credit_clicked.bmp");
	map["LEADERBOARD"] = new Texture("asset/texture/button/leaderboard.bmp");
	map["LEADERBOARD_CLICKED"] = new Texture("asset/texture/button/leaderboard_clicked.bmp");
	map["LEFT"] = new Texture("asset/texture/button/left.bmp");
	map["LEFT_CLICKED"] = new Texture("asset/texture/button/left_clicked.bmp");
	map["OPTION"] = new Texture("asset/texture/button/option.bmp");
	map["OPTION_CLICKED"] = new Texture("asset/texture/button/option_clicked.bmp");
	map["QUIT"] = new Texture("asset/texture/button/quit.bmp");
	map["QUIT_CLICKED"] = new Texture("asset/texture/button/quit_clicked.bmp");
	map["RIGHT"] = new Texture("asset/texture/button/right.bmp");
	map["RIGHT_CLICKED"] = new Texture("asset/texture/button/right_clicked.bmp");
	map["SFX"] = new Texture("asset/texture/button/sfx.bmp");
	map["SFX_CLICKED"] = new Texture("asset/texture/button/sfx_clicked.bmp");
	map["SPRITE"] = new Texture("asset/texture/button/sprite.bmp");
	map["SPRITE_CLICKED"] = new Texture("asset/texture/button/sprite_clicked.bmp");
	map["START"] = new Texture("asset/texture/button/start.bmp");
	map["START_CLICKED"] = new Texture("asset/texture/button/start_clicked.bmp");

	map["AMBULANCE_FRONT"] = new Texture("asset/texture/ambulance/front.bmp");
	map["AMBULANCE_BACK"] = new Texture("asset/texture/ambulance/back.bmp");
	map["CAR_BLUE_FRONT"] = new Texture("asset/texture/car/blue/front.bmp");
	map["CAR_BLUE_BACK"] = new Texture("asset/texture/car/blue/back.bmp");
	map["CAR_ORANGE_FRONT"] = new Texture("asset/texture/car/orange/front.bmp");
	map["CAR_ORANGE_BACK"] = new Texture("asset/texture/car/orange/back.bmp");
	map["TAXI_FRONT"] = new Texture("asset/texture/car/taxi/front.bmp");
	map["TAXI_BACK"] = new Texture("asset/texture/car/taxi/back.bmp");
	map["TRUCK_FRONT"] = new Texture("asset/texture/truck/front.bmp");
	map["TRUCK_BACK"] = new Texture("asset/texture/truck/back.bmp");

	map["GRASS"] = new Texture("asset/texture/lane/grass.bmp");
	map["GRASSFLOWER"] = new Texture("asset/texture/lane/grassflower.bmp");
	map["GRASSPEBBLE"] = new Texture("asset/texture/lane/grasspebble.bmp");
	map["ROAD"] = new Texture("asset/texture/lane/road.bmp");

	map["GOLD_CUP"] = new Texture("asset/texture/cup/gold.bmp");
	map["SILVER_CUP"] = new Texture("asset/texture/cup/silver.bmp");
	map["BRONZE_CUP"] = new Texture("asset/texture/cup/bronze.bmp");

	map["DUCK_DOWN"] = new Texture("asset/texture/sprite/duck/down.bmp");
	map["DUCK_LEFT"] = new Texture("asset/texture/sprite/duck/left.bmp");
	map["DUCK_RIGHT"] = new Texture("asset/texture/sprite/duck/right.bmp");
	map["DUCK_UP"] = new Texture("asset/texture/sprite/duck/up.bmp");
	map["DUCK_LARGE"] = new Texture("asset/texture/sprite/duck/large.bmp");

	map["CAT_DOWN"] = new Texture("asset/texture/sprite/cat/down.bmp");
	map["CAT_LEFT"] = new Texture("asset/texture/sprite/cat/left.bmp");
	map["CAT_RIGHT"] = new Texture("asset/texture/sprite/cat/right.bmp");
	map["CAT_UP"] = new Texture("asset/texture/sprite/cat/up.bmp");

	map["CHICKEN_DOWN"] = new Texture("asset/texture/sprite/chicken/down.bmp");
	map["CHICKEN_LEFT"] = new Texture("asset/texture/sprite/chicken/left.bmp");
	map["CHICKEN_RIGHT"] = new Texture("asset/texture/sprite/chicken/right.bmp");
	map["CHICKEN_UP"] = new Texture("asset/texture/sprite/chicken/up.bmp");

	map["TRAFFIC_RED"] = new Texture("asset/texture/traffic/red.bmp");
	map["TRAFFIC_GREEN"] = new Texture("asset/texture/traffic/green.bmp");

	map["VOLUME_MIN"] = new Texture("asset/texture/volume/0.bmp");
	map["VOLUME_LOW"] = new Texture("asset/texture/volume/25.bmp");
	map["VOLUME_MEDIUM"] = new Texture("asset/texture/volume/50.bmp");
	map["VOLUME_HIGH"] = new Texture("asset/texture/volume/75.bmp");
	map["VOLUME_MAX"] = new Texture("asset/texture/volume/100.bmp");
}

TextureHolder::~TextureHolder() {
	for(auto& it : map) delete it.second;
}

Texture* const TextureHolder::get(const std::string& name) const {
	return map.at(name);
}
