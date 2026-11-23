你截图里列出的这几个插件，基本覆盖了从启动动画、背景壁纸到桌面挂件的完整“桌面改造”流程。我帮你把每个插件的配置教程和关键步骤都整理出来了，可以对照着来操作。

### 🚀 1. dsh-startup-screen（启动动画）
这个插件用于自定义DSH的启动界面，包含“五步访问授权”等可交互步骤，并提供33项设置供你调整文案、配色等。
*   **安装**：推荐从 [Releases](https://github.com/QIFANAI/dsh-startup-screen/releases) 页面下载 `.tgz` 文件，然后使用命令 `dsh plugin --profile desktop add ./dsh-startup-screen-<版本>.tgz` 进行安装。
*   **配置**：安装并重启DSH后，进入 **设置 →「启动动画」** 即可调整各项参数。

### 🖼️ 2. dsh-plugin-wallpaper-engine（壁纸插件）
它能读取你本机Wallpaper Engine的素材库，一键将图片或视频设置为DSH界面的动态背景，并支持毛玻璃效果和明暗主题跟随。
*   **安装**：运行 `dsh plugin --profile web add @marlonlau/dsh-wallpaper-engine`。
*   **配置**：重启 `dsh web` 后，在 **设置 → Wallpaper Engine** 中选择壁纸即可。壁纸和额外目录等配置会保存在 `$DSH_HOME/storages/dsh-wallpaper-engine.json` 文件中。

### 🎬 3. dsh-boot-animation（开机动画/屏保）
这个插件在打开新对话或钉住的会话时，全屏播放一段视频作为开场动画，也支持在离开时显示屏保。
*   **安装**：使用命令 `dsh plugin --profile web add link:<你的本地路径>/dsh-boot-animation/package` 或从GitHub安装 `dsh plugin --profile web add github:NativeDog1/dsh-boot-animation`。
*   **配置**：所有设置都在 **设置 → 插件 →「启动动画」** 卡片里。你可以在这里打开**片头池**（`assets\videos\`）和**屏保池**（`assets\screensaver\`）的文件夹，放入自定义的 `.mp4`、`.gif` 或 Live2D 模型等素材。

### 🐳 4. dsh-whale-widget（小鲸鱼余额插件）
一只住在界面右下角的“小鲸鱼娘”，帮你盯着DeepSeek账户余额，支持拖拽和数字滚动动画。
*   **安装**：运行 `dsh plugin --profile web add dsh-whale-widget`。
*   **配置**：安装后需要确保DSH凭据里配置了 `DEEPSEEK_API_KEY`，因为这是拉取余额所必需的。其他无需额外设置，插件会自动工作。

### 👤 5. dsh-accountDisplayName-edit（显示昵称与头像）
这个插件可以替换侧边栏左下角的账号信息（如手机号或邮箱），并支持自定义头像，方便分享截图时保护隐私。
*   **安装**：**桌面端**需通过应用内的 **设置 → 插件** 或插件市场安装（CLI会拒绝操作desktop profile）；**Web端**可使用 `dsh plugin --profile web add github:AomiRaku/dsh-accountDisplayName-edit`。
*   **配置**：点击侧边栏底部的账号行，在菜单中选择 **「编辑显示名称」**，即可在弹出的窗口中修改名字或上传头像。保存空值可恢复默认。

### 🤖 6. dsh-boot-gate（AI编写的播放逻辑调节插件）
这个插件由AI编写并开源，用于调节启动播放的逻辑。注意，官方仓库名称可能是 **`dsh-boot-guard`**。
*   **安装**：使用命令 `dsh plugin --profile web add github:SaiSenBox/dsh-boot-guard`。
*   **配置**：安装并重启 `dsh web` 后，可在插件设置中调节启动逻辑。它默认只允许本机操作，如果确有需要，可以在启动DSH前设置环境变量 `DSH_BOOT_GUARD_ALLOW_REMOTE_MUTATION=1` 来放宽限制。

### 💡 几点提醒
*   **Profile选择**：桌面端和Web端的插件安装命令中的 `profile` 可能不同（`desktop` vs `web`），务必根据你的使用场景选择正确的命令。
*   **安装后重启**：大部分插件在安装后都需要**完全退出并重启DSH**（或至少重启 `dsh web`）才能生效。
*   **命令不生效时**：如果遇到 `dsh plugin` 命令找不到，可以尝试在命令前加上 `npx -p @deepseek-ai/dsh`，例如 `npx -p @deepseek-ai/dsh dsh plugin --profile web add ...`。