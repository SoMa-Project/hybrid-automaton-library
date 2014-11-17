#include "hybrid_automaton/ControlSwitch.h"

namespace ha {
	void ControlSwitch::add(const JumpConditionPtr& jump_condition)
	{
		_jump_conditions.push_back(jump_condition);
	}

	const std::vector<JumpConditionPtr>& ControlSwitch::getJumpConditions()
	{
		return _jump_conditions;
	}

	bool ControlSwitch::isActive() const {
		for (std::vector<JumpConditionPtr>::const_iterator it = _jump_conditions.begin(); it != _jump_conditions.end(); ++it) {
			if (!(*it)->isActive())
				return false;
		}
		return true;
	}

	void ControlSwitch::activate(const double& t) {
		for (std::vector<JumpConditionPtr>::const_iterator it = _jump_conditions.begin(); it != _jump_conditions.end(); ++it) {
			(*it)->activate(t);
		}
	}

	void ControlSwitch::deactivate() {
		for (std::vector<JumpConditionPtr>::const_iterator it = _jump_conditions.begin(); it != _jump_conditions.end(); ++it) {
			(*it)->deactivate();
		}
	}

	void ControlSwitch::step(const double& t) {
		for (std::vector<JumpConditionPtr>::const_iterator it = _jump_conditions.begin(); it != _jump_conditions.end(); ++it) {
			(*it)->step(t);
		}
	}

	void ControlSwitch::setName(const std::string& name) {
		_name = name;
	}

	const std::string ControlSwitch::getName() const {
		return _name;
	}

	void ControlSwitch::setSourceControlMode(const std::string& source) {
		_source_control_mode = source;
	}
	
	const std::string ControlSwitch::getSourceControlMode() const {
		return _source_control_mode;
	}

	void ControlSwitch::setTargetControlMode(const std::string& target) {
		_target_control_mode = target;
	}
	const std::string ControlSwitch::getTargetControlMode() const {
		return _target_control_mode;
	}

	DescriptionTreeNode::Ptr ControlSwitch::serialize(const DescriptionTree::ConstPtr& factory) const {
		DescriptionTreeNode::Ptr tree_node = factory->createNode("ControlSwitch");
		tree_node->setAttribute<std::string>(std::string("name"), this->getName());
		tree_node->setAttribute<std::string>(std::string("source"), this->getSourceControlMode());
		tree_node->setAttribute<std::string>(std::string("target"), this->getTargetControlMode());
		
		for (std::vector<JumpConditionPtr>::const_iterator it = _jump_conditions.begin(); it != _jump_conditions.end(); ++it) {
			DescriptionTreeNode::Ptr jc_node = factory->createNode("JumpCondition");
			tree_node->addChildNode(jc_node);
		}

		return tree_node;
	}
	
	void ControlSwitch::deserialize(const DescriptionTreeNode::ConstPtr& tree) {
		if (tree->getType() != "ControlSwitch") {
			std::stringstream ss;
			ss << "[ControlSwitch::deserialize] DescriptionTreeNode must have type 'ControlSwitch', not '" << tree->getType() << "'!";
			throw ss.str();
		}

		tree->getAttribute<std::string>("name", _name, "");
		tree->getAttribute<std::string>("source", _source_control_mode, "");
		tree->getAttribute<std::string>("target", _target_control_mode, "");
		
		if (_source_control_mode == "") {
			throw "[ControlSwitch::deserialize] source_control_mode must not be empty!";
		}
		if (_target_control_mode == "") {
			throw "[ControlSwitch::deserialize] target_control_mode must not be empty!";
		}

		DescriptionTreeNode::ConstNodeList jump_conditions;
		tree->getChildrenNodes("JumpCondition", jump_conditions);

		if (jump_conditions.empty()) {
			throw "[ControlSwitch::deserialize] No jump conditions found!";
		}

		DescriptionTreeNode::ConstNodeList::iterator js_it;
		for (js_it = jump_conditions.begin(); js_it != jump_conditions.end(); ++js_it) {
			JumpCondition::Ptr js(new JumpCondition);
			js->deserialize(*js_it);
			this->add(js);
		}
	}

}