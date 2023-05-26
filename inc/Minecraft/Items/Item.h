// File automatically generated from GenerateHeader.py
// https://github.com/FrederoxDev/Bedrock-GhidraScripts

#pragma once
#include <string>
#include <memory>

class ReadOnlyBinaryStream;
class Mob;
class Player;
class BaseGameVersion;
class ItemStackBase;
class Color;
class ItemDescriptor;
class BlockSource;
class TextureAtlasItem;
class Item;
class Container;
// class std::string;
class IDataInput;
class IDataOutput;
class Vec3;
class Actor;
class Block;
class Level;
class BlockPos;
// class Json::Value;
class ItemStack;
class CompoundTag;
class ItemInstance;
// struct std::string;
struct TextureUVCoordinateSet;
enum BlockShape;
enum InHandUpdateType;
enum CooldownType;
enum ItemUseMethod;
enum ItemAcquisitionMethod;
enum UseAnimation;

namespace Json {
	class Value;
};

enum CreativeItemCategory {
	All,
	Blocks,
	Decorations,
	Tools,
	Items,
	CommandOnly,
	None,
	TestCategory = 7
};

// r we ready to test? i dont know if ur done// yeah sorry// brb
// nothing showed up in the tab, expected, kk

class Item {
	char filler[0x1C0 - sizeof(void*)];
public:
	Item(const std::string&, short);
	virtual ~Item();
	virtual void tearDown();
	virtual int getMaxUseDuration(const ItemInstance*) const;
	virtual int getMaxUseDuration(const ItemStack*) const;
	virtual bool isExperimental(const ItemDescriptor*) const;
	virtual Item& setMaxStackSize(unsigned char);
	virtual Item& setCategory(CreativeItemCategory);
	virtual Item& setStackedByData(bool);
	virtual Item& setMaxDamage(int);
	virtual Item& setHandEquipped();
	virtual Item& setUseAnimation(UseAnimation);
	virtual Item& setMaxUseDuration(int);
	virtual Item& setRequiresWorldBuilder(bool);
	virtual Item& setExplodable(bool);
	virtual Item& setIsGlint(bool);
	virtual Item& setShouldDespawn(bool);
	virtual BlockShape getBlockShape() const;
	virtual bool canBeDepleted() const;
	virtual bool canDestroySpecial(const Block&) const;
	virtual int getLevelDataForAuxValue(int) const;
	virtual bool isStackedByData() const;
	virtual short getMaxDamage() const;
	virtual int getAttackDamage() const;
	virtual bool isHandEquipped() const;
	virtual bool isArmor() const;
	virtual bool isDye() const;
	virtual bool isFertilizer(int) const;
	virtual bool isGlint(const ItemStackBase&) const;
	virtual bool isThrowable() const;
	virtual bool isPattern() const;
	virtual bool showsDurabilityInCreative() const;
	virtual bool isWearableThroughLootTable(const std::unique_ptr<CompoundTag>&) const; //
	virtual bool canDestroyInCreative() const;
	virtual bool isDestructive(int) const;
	virtual bool isLiquidClipItem(int) const;
	virtual bool requiresInteract() const;
	virtual void appendFormattedHovertext(const ItemStackBase&, Level&, std::string&, const bool) const; //
	virtual bool isValidRepairItem(const ItemInstance&, const ItemInstance&) const;
	virtual int getEnchantSlot() const;
	virtual int getEnchantValue() const;
	virtual int getArmorValue() const;
	virtual bool isComplex() const;
	virtual bool isValidAuxValue(int) const;
	virtual int getDamageChance(int) const;
	virtual bool uniqueAuxValues() const;
	virtual bool isMultiColorTinted(const ItemStack&) const;
	virtual Color getColor(const std::unique_ptr<CompoundTag>&, const ItemDescriptor&) const; //
	virtual Color getBaseColor(const ItemStack&) const;
	virtual Color getSecondaryColor(const ItemStack&) const;
	virtual void saveAdditionalData(const ItemStackBase&, CompoundTag&) const;
	virtual void readAdditionalData(ItemStackBase&, const CompoundTag&) const;
	virtual bool isTintable() const;
	// buildIdAux // i cant find this one in ur headers
	// buildDescriptor //very good // should these be in the Item.h? my script found em, but they're not in your stuff
	// nah, it just need to have exactly 98 virtual functions with the dtor here
	virtual ItemStack& use(ItemStack&, Player&) const;
	virtual bool dispense(BlockSource&, Container&, int, const Vec3&, unsigned char) const;
	virtual ItemUseMethod useTimeDepleted(ItemInstance&, Level*, Player*) const;
	virtual ItemUseMethod useTimeDepleted(ItemStack&, Level*, Player*) const;
	virtual void releaseUsing(ItemInstance&, Player*, int) const;
	virtual void releaseUsing(ItemStack&, Player*, int) const;
	virtual float getDestroySpeed(const ItemInstance&, const Block&) const;
	virtual void hurtEnemy(ItemInstance&, Mob*, Mob*) const;
	virtual void hurtEnemy(ItemStack&, Mob*, Mob*) const;
	virtual bool mineBlock(ItemInstance&, const Block&, int, int, int, Actor*) const;
	virtual bool mineBlock(ItemStack&, const Block&, int, int, int, Actor*) const;
	virtual std::string buildDescriptionId(const ItemDescriptor&, const std::unique_ptr<CompoundTag>&) const; //
	virtual std::string buildEffectDescriptionName(const ItemStackBase&) const;
	virtual std::string buildCategoryDescriptionName() const;
	virtual void readUserData(ItemStackBase&, IDataInput&, ReadOnlyBinaryStream&) const;
	virtual void writeUserData(const ItemStackBase&, IDataOutput&) const;
	virtual unsigned char getMaxStackSize(const ItemDescriptor&) const;
	virtual bool inventoryTick(ItemStack&, Level&, Actor&, int, bool) const;
	virtual void refreshedInContainer(ItemStackBase&, Level&) const;
	virtual CooldownType getCooldownType() const;
	virtual int getCooldownTime() const;
	virtual void fixupOnLoad(ItemStackBase&) const;
	virtual void fixupOnLoad(ItemStackBase&, Level&) const;
	virtual short getDamageValue(const std::unique_ptr<CompoundTag>&) const; //
	virtual void setDamageValue(ItemStackBase&, short) const;
	virtual InHandUpdateType getInHandUpdateType(const Player&, const ItemInstance&, const ItemInstance&, bool, bool) const;
	virtual InHandUpdateType getInHandUpdateType(const Player&, const ItemStack&, const ItemStack&, bool, bool) const;
	virtual bool isSameItem(const ItemStackBase&, const ItemStackBase&) const;
	virtual std::string getInteractText(const Player&) const;
	virtual int getAnimationFrameFor(Mob*, bool, const ItemStack*, bool) const;
	virtual bool isEmissive(int) const;
	virtual const TextureUVCoordinateSet& getIcon(const ItemStackBase&, int, bool) const;
	virtual int getIconYOffset() const;
	virtual Item& setIcon(const std::string&, int); //
	virtual Item& setIcon(const TextureUVCoordinateSet&);
	virtual Item& setIconAtlas(const std::string&, int); //
	virtual bool canBeCharged() const;
	virtual void playSoundIncrementally(const ItemInstance&, Mob&) const;
	virtual void playSoundIncrementally(const ItemStack&, Mob&) const;
	virtual std::string getAuxValuesDescription() const;
private:
	virtual bool _checkUseOnPermissions(Actor&, ItemInstance&, const unsigned char&, const BlockPos&) const;
	virtual bool _checkUseOnPermissions(Actor&, ItemStack&, const unsigned char&, const BlockPos&) const;
	virtual bool _calculatePlacePos(ItemInstance&, Actor&, unsigned char&, BlockPos&) const;
	virtual bool _calculatePlacePos(ItemStack&, Actor&, unsigned char&, BlockPos&) const;
	virtual bool _useOn(ItemInstance&, Actor&, BlockPos, unsigned char, float, float, float) const;
	virtual bool _useOn(ItemStack&, Actor&, BlockPos, unsigned char, float, float, float) const;

	// Begin Non-Virtual Functions
public:
	bool initServer(Json::Value&);
	static void beginCreativeGroup(const std::string&, const ItemInstance&);
	static void beginCreativeGroup(const std::string&, const Block*, const CompoundTag*);
	static void beginCreativeGroup(const std::string&, Item*, short, const CompoundTag*);
	static void beginCreativeGroup(const std::string&, short, short, const CompoundTag*);
	static void addCreativeItem(const Block&);
	static void addCreativeItem(Item*, short);
	static void addCreativeItem(const ItemInstance&);
	static void addCreativeItem(const ItemStack&);
	Item& setMinRequiredBaseGameVersion(const BaseGameVersion&);
	Item& setIsMirroredArt(bool);
	bool updateCustomBlockEntityTag(BlockSource&, ItemStack&, BlockPos&) const;
	bool useOn(ItemStack&, Actor&, int, int, int, unsigned char, float, float, float) const;
	Item& setAllowOffhand(bool);
	std::string buildDescriptionName(const ItemStackBase&) const;
	static TextureUVCoordinateSet getTextureUVCoordinateSet(const std::string&, int);
	static const TextureUVCoordinateSet& getIconTextureUVSet(const TextureAtlasItem&, int, int);
	static const TextureAtlasItem& getTextureItem(const std::string&);
	const std::string& getCommandName() const;
	std::string getSerializedName() const;
protected:
	float destroySpeedBonus(const ItemInstance&) const;
	void _helpChangeInventoryItemInPlace(Actor&, ItemStack&, ItemStack&, ItemAcquisitionMethod) const;

	// Begin Variables
	// public: static bool const Item::mGenerateDenyParticleEffect;
	// public: static class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const Item::TAG_DAMAGE;
	// public: static class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const Item::ICON_DESCRIPTION_PREFIX;
	// public: static struct TextureUVCoordinateSet Item::mInvalidTextureUVCoordinateSet;
	// public: static bool Item::mAllowExperimental;
	// public: static bool Item::mInCreativeGroup;
	// public: static class std::weak_ptr<class AtlasItemManager> Item::mItemTextureItems;
	// public: static class std::vector<class ItemInstance,class std::allocator<class ItemInstance> > Item::mCreativeList;
	// public: static class std::mutex Item::mCreativeListMutex;
	// public: static class std::vector<class ItemStack,class std::allocator<class ItemStack> > Item::mCreativeListStack;
	// public: static class std::vector<class std::vector<class ItemInstance,class std::allocator<class ItemInstance> >,class std::allocator<class std::vector<class ItemInstance,class std::allocator<class ItemInstance> > > > Item::mCreativeGroups;
	// public: static class std::vector<struct CreativeGroupInfo,class std::allocator<struct CreativeGroupInfo> > Item::mCreativeGroupInfo;
	// public: static class BaseGameVersion Item::mWorldBaseGameVersion;
};