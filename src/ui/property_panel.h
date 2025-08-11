#pragma once
#include "../add-ons/imgui_widgets.h"
#include "../elems/light.h"
#include "../elems/mesh.h"
#include "file/ImFileBrowser.h"
#include "imgui.h"
#include "scene_view.h"
#include "../pch.h"
#include <iostream>

namespace nui {
	class Property_Panel {
	public:
		Property_Panel() {
			mCurrentFile = "<...>";

			// (optional) set browser properties
			mFileDialog.SetTitle("title");
			mFileDialog.SetTypeFilters({ ".fbx", ".obj" });

		}
		void render(nui::SceneView* mScene);
		 
		void set_mesh_load_callback(const std::function<void(const std::string&)>& callback)
		{
			mMeshLoadCallback = callback;
		}

	private:
		// create a file browser instance
		ImGui::FileBrowser mFileDialog;

		std::function<void(const std::string&)> mMeshLoadCallback;

		std::string mCurrentFile;
	};
}