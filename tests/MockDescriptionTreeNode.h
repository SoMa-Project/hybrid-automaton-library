#include "hybrid_automaton/DescriptionTreeNode.h"

namespace ha {

	class MockDescriptionTreeNode : public DescriptionTreeNode {
	public:
		MOCK_CONST_METHOD0(getType, const std::string () );
		MOCK_CONST_METHOD2(getAttributeString, bool (const std::string& field_name, std::string& field_value) );
		MOCK_CONST_METHOD2(getChildrenNodes, bool (const std::string& type, ConstNodeList& children) );
		MOCK_CONST_METHOD1(getChildrenNodes, bool (ConstNodeList& children) );

		MOCK_METHOD2(setAttributeString, void (const std::string& field_name, const std::string& field_value) );
		MOCK_METHOD1(addChildNode, void (const DescriptionTreeNode::Ptr& child) );
	};

}