#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
struct Images {

	std::string image_name;
	int ImageSize;
	int ImageResolution;

};

static std::vector<Images> images_vec{};


//;

class IImageViewer {
public:
	virtual ~IImageViewer() noexcept {

	}

	//virtual void LoadImages(Images& img, int amount_of_load_image) = 0;
	virtual void DisplayImage(std::string& image_name) = 0;
};

class ImageViewer : public IImageViewer {
public:
	ImageViewer(Images& img)   {
		m_images = img;
		images_vec.push_back(AddImagesToTheApp(img, img.image_name, img.ImageResolution, img.ImageSize));
	}

	~ImageViewer() noexcept override = default;

	//void LoadImages(Images& img,int amount_of_load_image) override {
	//}

	void DisplayImage(std::string& image_name) override {
		std::cout << "displayed_image.ImageName: " << m_images.image_name << " displayed_image.ImageResolution" << m_images.ImageResolution << " displayed_image.ImageSize: " << m_images.ImageSize << std::endl;

	}


private:
	Images m_images;
	Images AddImagesToTheApp(Images& img, const std::string& name, int ImageRes, int ImageSize) {
			img.image_name = name;
			img.ImageResolution = ImageRes;
			img.ImageSize = ImageSize;

			return img;
	}

};

class ImageViewerProxy : public IImageViewer {
public:
	ImageViewerProxy() {
		
	}

	void DisplayImage(std::string& image_name) override
	{
		if (CheckIsImageLoaded(image_name) != false) {
			std::cout << " Image is already loaded current instance can be still use\n";
		}
		else if(CheckIsImageLoaded(image_name) != true) {
			std::cout << " Image is not loaded yet new instance will be created\n";
			//create new instance for new loading image
			Images img{ image_name, 2, 2 };
			auto iv = std::make_unique<ImageViewer>(img);
			viewers_.emplace(image_name, std::move(iv));
		}
			//this image is already loaded before using it directly.
		viewers_[image_name]->DisplayImage(image_name);
	}

	~ImageViewerProxy() noexcept override = default;

private:
	std::unordered_map<std::string, std::unique_ptr<IImageViewer>> viewers_;

	bool CheckIsImageLoaded(std::string& name) {
		auto image = std::find_if(images_vec.begin(), images_vec.end(), [=](const Images& img) -> bool {
			if (img.image_name == name) {
				return true;
			}
			else {
				return false;
			}

			});
		if (image != images_vec.end()) {
			return true;
		}
		return false;
	}
};
