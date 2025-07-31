# L4D2_PluginDemo 调试日志记录
## 2025.7.28:
1. CWeaponPortalgun是最小子类，无继承
2. 实体与类之间关联宏：LINK_ENTITY_TO_CLASS
3. datamap.h：替换为portal sdk中的同名文件，否则BEGIN_DATADESC和DEFINE_FIELD有宏展开报错“初始值设定项值太多”错误（L4D2SDK中的datamap.h重命名为datamap.h.l4d2version，portal中的同名文件复制进SDK路径）
4. OBBMinsPreScaled和OBBMaxsPreScaled在L4D2SDK中不存在：src\game\shared\portal\portal_util_shared.cpp
5. CBaseEntity::IncrementInterpolationFrame(在src\game\server\baseentity.cpp)在L4D2SDK中不存在，但是使用的地方不多，如果游戏内确实不存在，调用可能崩溃，因此先注释掉该函数的所有调用；
6. src\public\vphysics_interface.h中，surfacesoundhandles_t的定义存在差异，导致src\game\shared\physics_shared.cpp中的实现被注销掉两行里面编译失败；
7. IVEngineServer的Timer接口在求生之路2中对应函数签名改为OBSOLETE_Time，作用相同，game\server\physics.cpp代码调用位置相应做出修改；
8. movevars_shared.cpp：L4D2SDK中缺少GetCurrentGravity函数，并且在使用两套sdk的情况下，编译阶段一旦包含L4D2的SDK后宏将起作用，便不会再重复包含PortalSDK的同名文件；
9. CSteamAPIContext类（src\public\steam\steam_api.h）的实现通过宏VERSION_SAFE_STEAM_API_INTERFACES隔离，但是调用和定义并没有隔离，造成编译找不到符号，此处L4D2SDK和PortalSDK两个文件是线上亦有差距。适配上选择通过相同的宏VERSION_SAFE_STEAM_API_INTERFACES隔离所有调用
10. CServerGameDLL对纯虚基类IServerGameDLL的实现不全，导致无法实例化对象，尝试拿IServerGameDLL的接口调用了没有覆写的方法ServerHibernationUpdate，确实可以调用，所以要对CServerGameDLL改造以实现基类的纯虚接口，所在文件在src\game\server\gameinterface.h
11. IVEngineServer基类的方法PEntityOfEntIndex已经被移除，参考：https://wiki.alliedmods.net/Porting_to_Left_4_Dead

## 2025.7.29:
12. 在src\game\server\gameinterface.cpp中，CServerGameDLL::PreClientUpdate函数中PEntityOfEntIndex语句注释（CServerGameDLL::PreClientUpdate绘制hitbox,PEntityOfEntIndex在L4D2已经废弃,先不要了）
12. 在src\game\server\gameinterface.cpp中，CServerGameEnts::CheckTransmit函数中PEntityOfEntIndex已被等价替代
13. CServerGameEnts没有覆写IServerGameEnts的PrepareForFullUpdate方法, github上这个方法也有一些空实现,暂且增加一个空实现
14. IServerGameClients类四个纯虚接口缺少实现:ClientVoice、GetMaxSplitscreenPlayers、GetMaxHumanPlayers、ClientCommandKeyValues，分别生成空实现或者默认返回
15. src\game\server\portal\PortalSimulation.cpp中CPSCollisionEntity::Spawn存在对IncrementInterpolationFrame的调用, 暂且注释
16. src\game\server\gameinterface.cpp::UserMessageBegin方法缺少一个参数,已修复

## 2025.7.30:
17. engine->PEntityOfEntIndex(i)等价替代为:(i >= 0 && i < gpGlobals->maxEntities) ? (edict_t*)(gpGlobals->pEdicts + i) : NULL;

## 2025.8.1:
18. 以src\game\server\portal\portal_player.cpp为例，对Studio_BuildMatrices函数的调用需要注释掉倒数第三个float参数，才能与函数签名匹配：调用方在PortalSDK，函数定义在l4d2sdk（src\public\bone_setup.cpp）