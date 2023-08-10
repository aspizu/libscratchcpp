// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <scratchcpp/iengine.h>
#include <scratchcpp/target.h>
#include <unordered_map>
#include <memory>
#include <chrono>

#include "global.h"
#include "blocksectioncontainer.h"

namespace libscratchcpp
{

class Entity;

class Engine : public IEngine
{
    public:
        Engine();
        Engine(const Engine &) = delete;

        void clear() override;
        void resolveIds();
        void compile() override;

        void frame() override;
        void start() override;
        void stop() override;
        void startScript(std::shared_ptr<Block> topLevelBlock, std::shared_ptr<Target> target) override;
        void broadcast(unsigned int index, VirtualMachine *sourceScript, bool wait = false) override;
        void stopScript(VirtualMachine *vm) override;
        void stopTarget(Target *target, VirtualMachine *exceptScript) override;
        void run() override;

        bool broadcastRunning(unsigned int index, VirtualMachine *sourceScript) override;

        void breakFrame() override;
        bool breakingCurrentFrame() override;

        void skipFrame() override;
        void lockFrame() override;

        void registerSection(std::shared_ptr<IBlockSection> section) override;
        unsigned int functionIndex(BlockFunc f) override;

        void addCompileFunction(IBlockSection *section, const std::string &opcode, BlockComp f) override;
        void addHatBlock(IBlockSection *section, const std::string &opcode) override;
        void addInput(IBlockSection *section, const std::string &name, int id) override;
        void addField(IBlockSection *section, const std::string &name, int id) override;
        void addFieldValue(IBlockSection *section, const std::string &value, int id) override;

        const std::vector<std::shared_ptr<Broadcast>> &broadcasts() const override;
        void setBroadcasts(const std::vector<std::shared_ptr<Broadcast>> &broadcasts) override;
        std::shared_ptr<Broadcast> broadcastAt(int index) const override;
        int findBroadcast(const std::string &broadcastName) const override;
        int findBroadcastById(const std::string &broadcastId) const override;

        void addBroadcastScript(std::shared_ptr<Block> whenReceivedBlock, std::shared_ptr<Broadcast> broadcast) override;

        const std::vector<std::shared_ptr<Target>> &targets() const override;
        void setTargets(const std::vector<std::shared_ptr<Target>> &newTargets) override;
        Target *targetAt(int index) const override;
        int findTarget(const std::string &targetName) const override;

        const std::vector<std::string> &extensions() const override;
        void setExtensions(const std::vector<std::string> &newExtensions) override;

        const std::unordered_map<std::shared_ptr<Block>, std::shared_ptr<Script>> &scripts() const override;

    private:
        std::shared_ptr<Block> getBlock(const std::string &id);
        std::shared_ptr<Variable> getVariable(const std::string &id);
        std::shared_ptr<List> getList(const std::string &id);
        std::shared_ptr<Broadcast> getBroadcast(const std::string &id);
        std::shared_ptr<Entity> getEntity(const std::string &id);
        std::shared_ptr<IBlockSection> blockSection(const std::string &opcode) const;
        BlockSectionContainer *blockSectionContainer(const std::string &opcode) const;
        BlockSectionContainer *blockSectionContainer(IBlockSection *section) const;

        std::unordered_map<std::shared_ptr<IBlockSection>, std::unique_ptr<BlockSectionContainer>> m_sections;
        std::vector<std::shared_ptr<Target>> m_targets;
        std::vector<std::shared_ptr<Broadcast>> m_broadcasts;
        std::unordered_map<unsigned int, std::vector<Script *>> m_broadcastMap;
        std::unordered_map<unsigned int, std::vector<std::pair<VirtualMachine *, VirtualMachine *>>> m_runningBroadcastMap; // source script, "when received" script
        std::vector<std::string> m_extensions;
        std::vector<std::shared_ptr<VirtualMachine>> m_runningScripts;
        std::vector<VirtualMachine *> m_scriptsToRemove;
        std::unordered_map<std::shared_ptr<Block>, std::shared_ptr<Script>> m_scripts;
        std::vector<BlockFunc> m_functions;

        bool m_breakFrame = false;
        bool m_skipFrame = false;
        bool m_lockFrame = false;
};

} // namespace libscratchcpp
