//reusing code from "SFML Game Development"

#include "BloomEffect.hpp"

BloomEffect::BloomEffect():
shaders(),
brightnessTexture(),
firstPassTextures(),
secondPassTextures(){

	shaders.load(Shaders::brightness, "Shaders/Fullpass.vert", "Shaders/Brightness.frag");
	shaders.load(Shaders::downSample, "Shaders/Fullpass.vert", "Shaders/DownSample.frag");
	shaders.load(Shaders::gaussianBlur, "Shaders/Fullpass.vert", "Shaders/GuassianBlur.frag");
	shaders.load(Shaders::add, "Shaders/Fullpass.vert", "Shaders/Add.frag");
}

void BloomEffect::apply(const sf::RenderTexture& input, sf::RenderTarget& output){

	prepareTextures(input.getSize());

	filterBright(input, brightnessTexture);

	downsample(brightnessTexture, firstPassTextures[0]);
	blurMultipass(firstPassTextures);

	downsample(firstPassTextures[0], secondPassTextures[0]);
	blurMultipass(secondPassTextures);

	add(firstPassTextures[0], secondPassTextures[0], firstPassTextures[1]);
	firstPassTextures[1].display();
	add(input, firstPassTextures[1], output);
}

void BloomEffect::prepareTextures(sf::Vector2u size){

	if (brightnessTexture.getSize() != size){

		brightnessTexture.create(size.x, size.y);
		brightnessTexture.setSmooth(true);

		firstPassTextures[0].create(size.x / 2, size.y / 2);
		firstPassTextures[0].setSmooth(true);
		firstPassTextures[1].create(size.x / 2, size.y / 2);
		firstPassTextures[1].setSmooth(true);

		secondPassTextures[0].create(size.x / 4, size.y / 4);
		secondPassTextures[0].setSmooth(true);
		secondPassTextures[1].create(size.x / 4, size.y / 4);
		secondPassTextures[1].setSmooth(true);
	}
}

void BloomEffect::filterBright(const sf::RenderTexture& input, sf::RenderTexture& output){

	sf::Shader& brightness = shaders.get(Shaders::brightness);

	brightness.setParameter("source", input.getTexture());
	applyShader(brightness, output);
	output.display();
}

void BloomEffect::blurMultipass(RenderTextureArray& renderTextures){

	sf::Vector2u textureSize = renderTextures[0].getSize();

	for (std::size_t count = 0; count < 2; ++count){

		blur(renderTextures[0], renderTextures[1], sf::Vector2f(0.f, 1.f / textureSize.y));
		blur(renderTextures[1], renderTextures[0], sf::Vector2f(1.f / textureSize.x, 0.f));
	}
}

void BloomEffect::blur(const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor)
{
	sf::Shader& gaussianBlur = shaders.get(Shaders::gaussianBlur);

	gaussianBlur.setParameter("source", input.getTexture());
	gaussianBlur.setParameter("offsetFactor", offsetFactor);
	applyShader(gaussianBlur, output);
	output.display();
}

void BloomEffect::downsample(const sf::RenderTexture& input, sf::RenderTexture& output)
{
	sf::Shader& downSampler = shaders.get(Shaders::downSample);

	downSampler.setParameter("source", input.getTexture());
	downSampler.setParameter("sourceSize", sf::Vector2f(input.getSize()));
	applyShader(downSampler, output);
	output.display();
}

void BloomEffect::add(const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& output)
{
	sf::Shader& adder = shaders.get(Shaders::add);

	adder.setParameter("source", source.getTexture());
	adder.setParameter("bloom", bloom.getTexture());
	applyShader(adder, output);
}
