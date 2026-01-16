#!/bin/bash
# Xcode Setup Script for UE5 Development
# Run this AFTER installing Xcode from App Store

set -e  # Exit on error

echo "=========================================="
echo "Xcode Setup for UE5 - Football 7v7 Project"
echo "=========================================="
echo ""

# Check if Xcode is installed
if [ ! -d "/Applications/Xcode.app" ]; then
    echo "❌ ERROR: Xcode not found in /Applications/"
    echo ""
    echo "Please install Xcode first:"
    echo "1. Open App Store"
    echo "2. Search for 'Xcode'"
    echo "3. Click 'Get' or 'Install'"
    echo "4. Wait for installation to complete"
    echo "5. Run this script again"
    exit 1
fi

echo "✓ Xcode found"

# Install Command Line Tools
echo ""
echo "Installing Command Line Tools..."
xcode-select --install 2>/dev/null || echo "✓ Command Line Tools already installed"

# Set Xcode path
echo ""
echo "Setting Xcode developer directory..."
sudo xcode-select --switch /Applications/Xcode.app/Contents/Developer

# Verify path
XCODE_PATH=$(xcode-select -p)
echo "✓ Xcode path set to: $XCODE_PATH"

# Accept license
echo ""
echo "Accepting Xcode license..."
sudo xcodebuild -license accept
echo "✓ License accepted"

# Verify installation
echo ""
echo "=========================================="
echo "Verifying Installation..."
echo "=========================================="

# Check Xcode version
echo ""
echo "Xcode version:"
xcodebuild -version

# Check compiler
echo ""
echo "Clang compiler:"
clang --version | head -n 1

# Check if Homebrew is installed
echo ""
if ! command -v brew &> /dev/null; then
    echo "⚠️  Homebrew not found. Installing..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

    # Add Homebrew to PATH (for Apple Silicon Macs)
    if [ -d "/opt/homebrew" ]; then
        echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
        eval "$(/opt/homebrew/bin/brew shellenv)"
    fi
fi

echo "✓ Homebrew installed"

# Install additional tools
echo ""
echo "Installing additional build tools..."
brew install cmake 2>/dev/null || brew upgrade cmake
brew install git-lfs 2>/dev/null || brew upgrade git-lfs

echo "✓ CMake installed: $(cmake --version | head -n 1)"
echo "✓ Git LFS installed: $(git lfs version)"

# Check for UE5
echo ""
echo "=========================================="
echo "Checking for Unreal Engine 5..."
echo "=========================================="

UE5_PATHS=(
    "/Users/Shared/Epic Games/UE_5.3"
    "/Users/Shared/Epic Games/UE_5.4"
    "$HOME/Library/Application Support/Epic/UnrealEngine/UE_5.3"
    "$HOME/Library/Application Support/Epic/UnrealEngine/UE_5.4"
)

UE5_FOUND=false
for UE5_PATH in "${UE5_PATHS[@]}"; do
    if [ -d "$UE5_PATH" ]; then
        echo "✓ Found UE5 at: $UE5_PATH"
        UE5_FOUND=true
        export UE5_ENGINE_PATH="$UE5_PATH"
        break
    fi
done

if [ "$UE5_FOUND" = false ]; then
    echo "⚠️  Unreal Engine 5 not found"
    echo ""
    echo "Please install UE5 from Epic Games Launcher:"
    echo "https://www.unrealengine.com/download"
else
    # Check if project exists
    echo ""
    echo "=========================================="
    echo "Checking Football 7v7 Project..."
    echo "=========================================="

    if [ -f "$HOME/Documents/7v7/Football7v7.uproject" ]; then
        echo "✓ Project found at: $HOME/Documents/7v7"

        echo ""
        echo "Do you want to generate Xcode project files now? (y/n)"
        read -r GENERATE

        if [ "$GENERATE" = "y" ] || [ "$GENERATE" = "Y" ]; then
            echo "Generating Xcode project files..."
            cd "$HOME/Documents/7v7"
            "$UE5_ENGINE_PATH/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh" \
                -project="$HOME/Documents/7v7/Football7v7.uproject" -game -engine
            echo "✓ Xcode project files generated"

            echo ""
            echo "Opening project..."
            open Football7v7.xcworkspace || open Football7v7.uproject
        fi
    else
        echo "⚠️  Project not found at $HOME/Documents/7v7"
        echo ""
        echo "Clone the repository first:"
        echo "  cd ~/Documents"
        echo "  git clone <repository-url> 7v7"
    fi
fi

echo ""
echo "=========================================="
echo "✅ Setup Complete!"
echo "=========================================="
echo ""
echo "Next steps:"
echo "1. Clone the Football 7v7 repository (if not done)"
echo "2. Double-click Football7v7.uproject to open in UE5"
echo "3. Wait for C++ compilation (first time takes 5-10 min)"
echo "4. Follow README_ENHANCED.md for gameplay setup"
echo ""
echo "Happy coding! 🏈"
