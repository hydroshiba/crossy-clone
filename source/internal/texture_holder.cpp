#include "texture_holder.hpp"

TextureHolder::TextureHolder() {
	map["TITLE"] = new Texture("asset/texture/title.bmp");

	map["CREDIT_ASTRAUNAUT"] = new Texture("asset/texture/credit/astraunaut.bmp");
	map["CREDIT_CAT"] = new Texture("asset/texture/credit/cat.bmp");
	map["CREDIT_FOX"] = new Texture("asset/texture/credit/fox.bmp");
	map["CREDIT_SEAL"] = new Texture("asset/texture/credit/seal.bmp");
	map["CREDIT_TEACHER"] = new Texture("asset/texture/credit/3T.bmp");
	
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

	map["A"] = new Texture("asset/font/A.bmp");
	map["B"] = new Texture("asset/font/B.bmp");
	map["C"] = new Texture("asset/font/C.bmp");
	map["D"] = new Texture("asset/font/D.bmp");
	map["E"] = new Texture("asset/font/E.bmp");
	map["F"] = new Texture("asset/font/F.bmp");
	map["G"] = new Texture("asset/font/G.bmp");
	map["H"] = new Texture("asset/font/H.bmp");
	map["I"] = new Texture("asset/font/I.bmp");
	map["J"] = new Texture("asset/font/J.bmp");
	map["K"] = new Texture("asset/font/K.bmp");
	map["L"] = new Texture("asset/font/L.bmp");
	map["M"] = new Texture("asset/font/M.bmp");
	map["N"] = new Texture("asset/font/N.bmp");
	map["O"] = new Texture("asset/font/O.bmp");
	map["P"] = new Texture("asset/font/P.bmp");
	map["Q"] = new Texture("asset/font/Q.bmp");
	map["R"] = new Texture("asset/font/R.bmp");
	map["S"] = new Texture("asset/font/S.bmp");
	map["T"] = new Texture("asset/font/T.bmp");
	map["U"] = new Texture("asset/font/U.bmp");
	map["V"] = new Texture("asset/font/V.bmp");
	map["W"] = new Texture("asset/font/W.bmp");
	map["X"] = new Texture("asset/font/X.bmp");
	map["Y"] = new Texture("asset/font/Y.bmp");
	map["Z"] = new Texture("asset/font/Z.bmp");
	
	map["0"] = new Texture("asset/font/0.bmp");
	map["1"] = new Texture("asset/font/1.bmp");
	map["2"] = new Texture("asset/font/2.bmp");
	map["3"] = new Texture("asset/font/3.bmp");
	map["4"] = new Texture("asset/font/4.bmp");
	map["5"] = new Texture("asset/font/5.bmp");
	map["6"] = new Texture("asset/font/6.bmp");
	map["7"] = new Texture("asset/font/7.bmp");
	map["8"] = new Texture("asset/font/8.bmp");
	map["9"] = new Texture("asset/font/9.bmp");
}

TextureHolder::~TextureHolder() {
	for(auto& it : map) delete it.second;
}

Texture* const TextureHolder::get(const std::string& name) const {
	if(map.find(name) == map.end()) throw std::runtime_error("TextureHolder::get() : Texture " + name + " not found");
	return map.at(name);
}
