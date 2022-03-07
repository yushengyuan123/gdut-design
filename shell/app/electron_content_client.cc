#include "shell/app/electron_content_client.h"

#include <string>
#include <utility>
#include <vector>

#include "base/strings/string_util.h"
#include "ui/base/resource/resource_bundle.h"

namespace electron {
  ElectronContentClient::ElectronContentClient() = default;

  ElectronContentClient::~ElectronContentClient() = default;

  base::StringPiece ElectronContentClient::GetDataResource(
      int resource_id,
      ui::ResourceScaleFactor scale_factor) {
    return ui::ResourceBundle::GetSharedInstance().GetRawDataResourceForScale(
        resource_id, scale_factor);
  }
}