cmd_Release/addon.node := ln -f "Release/obj.target/addon.node" "Release/addon.node" 2>/dev/null || (rm -rf "Release/addon.node" && cp -af "Release/obj.target/addon.node" "Release/addon.node")
