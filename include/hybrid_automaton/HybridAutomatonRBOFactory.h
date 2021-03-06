/*
 * Copyright 2015-2017, Robotics and Biology Lab, TU Berlin
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright 
 * notice, this list of conditions and the following disclaimer in the 
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef HYBRID_AUTOMATON_RBO_FACTORY_H
#define HYBRID_AUTOMATON_RBO_FACTORY_H

#include "hybrid_automaton/HybridAutomaton.h"
#include "hybrid_automaton/HybridAutomatonAbstractFactory.h"

#include <boost/shared_ptr.hpp>



#define DEFAULT_NUM_DOF_ARM 7
#define DEFAULT_NUM_DOF_BASE 3

#define DEFAULT_MAX_VEL_JS_ARM 0.3
#define DEFAULT_MAX_VEL_JS_BASE 0.15

#define DEFAULT_KP_JS_ARM 0.0
#define DEFAULT_KV_JS_ARM 0.0
#define DEFAULT_KP_JS_BASE 40.0
#define DEFAULT_KV_JS_BASE 7.0

#define DEFAULT_KP_JS_NAKAMURA_ARM 15.0
#define DEFAULT_KP_JS_NAKAMURA_BASE 0.0
#define DEFAULT_KV_JS_NAKAMURA_ARM 0.5
#define DEFAULT_KV_JS_NAKAMURA_BASE 5.0

#define DEFAULT_JOINT_WEIGHTS_NAKAMURA_ARM 1.0
#define DEFAULT_JOINT_WEIGHTS_NAKAMURA_BASE 0.5
#define DEFAULT_JOINT_WEIGHTS_NAKAMURA_BASE_LITTLE_MOTION 0.01

#define DEFAULT_KP_OS_LINEAR 0.0
#define DEFAULT_KP_OS_ANGULAR 0.0
#define DEFAULT_KV_OS_LINEAR 10.0
#define DEFAULT_KV_OS_ANGULAR 10.0

#define DEFAULT_HOME_CONFIG_JS_ARM 0.0
#define DEFAULT_HOME_CONFIG_JS_BASE 0.0

#define DEFAULT_POS_EPSILON_JS_ARM 0.13
#define DEFAULT_POS_EPSILON_JS_BASE 0.05
#define DEFAULT_VEL_EPSILON_JS_ARM 0.01
#define DEFAULT_VEL_EPSILON_JS_BASE 0.001
#define DEFAULT_VEL_GOAL_JS_ARM 0.0
#define DEFAULT_VEL_GOAL_JS_BASE 0.0

#define DEFAULT_POS_EPSILON_OS_LINEAR 0.01
#define DEFAULT_POS_EPSILON_OS_ANGULAR 0.01
#define DEFAULT_VEL_EPSILON_OS_LINEAR 0.01
#define DEFAULT_VEL_EPSILON_OS_ANGULAR 0.01
#define DEFAULT_VEL_GOAL_OS_LINEAR 0.0
#define DEFAULT_VEL_GOAL_OS_ANGULAR 0.0

#define DEFAULT_MAX_VEL_OS_LINEAR 0.03
#define DEFAULT_MAX_VEL_OS_ANGULAR 0.5

#define DEFAULT_UPDATE_RATE 100



namespace ha {

/**
     * @brief Concatenates two vectors, one for the arm and one for the base
     *
     * @param arm_vector Vector for the arm. It will be the first _num_dof_arm values of the resulting vector
     * @param base_vector Vector for the base. It will be the last _num_dof_base of the resulting vector
     * @return Eigen::MatrixXd Resulting vector that contains both input vectors
     */
Eigen::MatrixXd _combineArmAndBase(const Eigen::MatrixXd& arm_vector, const Eigen::MatrixXd base_vector);


Eigen::MatrixXd mask_by_index(const Eigen::MatrixXd m, const Eigen::MatrixXd index_vec);

class HybridAutomatonRBOFactory;
typedef boost::shared_ptr<HybridAutomatonRBOFactory> HybridAutomatonRBOFactoryPtr;
typedef boost::shared_ptr<const HybridAutomatonRBOFactory> HybridAutomatonRBOFactoryConstPtr;

struct HybridAutomatonRBOParams : public HybridAutomatonAbstractParams
{
    std::string name, topic_name, parent_frame, child_frame;
    Eigen::MatrixXd goal1, goal2;
    Eigen::MatrixXd kp1, kp2;
    Eigen::MatrixXd kv1, kv2;
    Eigen::MatrixXd max_vel_js, max_velocity1, max_velocity2;
    Eigen::MatrixXd index_vec;
    bool goal_relative, use_tf, trajectory;
    int update_rate;
    double completion_time;





    /// Maximum joint space (js) velocity
    Eigen::MatrixXd max_vel_js_arm;
    Eigen::MatrixXd max_vel_js_base;

    /// Joint space (js) gains
    Eigen::MatrixXd kp_js_arm;
    Eigen::MatrixXd kp_js_base;
    Eigen::MatrixXd kv_js_arm;
    Eigen::MatrixXd kv_js_base;
    Eigen::MatrixXd kp_js;
    Eigen::MatrixXd kv_js;


    /// Operational space gains (3x orientation + 3x position)
    Eigen::MatrixXd _kp_os_linear;
    Eigen::MatrixXd _kp_os_angular;
    Eigen::MatrixXd _kv_os_linear;
    Eigen::MatrixXd _kv_os_angular;

    /// Joint space integration gains for operational space Nakamura control set
    Eigen::MatrixXd _kp_js_nakamura_arm;
    Eigen::MatrixXd _kp_js_nakamura_base;
    Eigen::MatrixXd _kv_js_nakamura_arm;
    Eigen::MatrixXd _kv_js_nakamura_base;

    /// Weights of each joint for operational space Nakamura control set
    Eigen::MatrixXd _joint_weights_nakamura_arm;
    Eigen::MatrixXd _joint_weights_nakamura_base;
    Eigen::MatrixXd _joint_weights_nakamura_base_no_rotation;
    Eigen::MatrixXd _joint_weights_nakamura_base_little_motion;







    //    /// Convergence goal for the velocity of a joint space (js) controller
    //    Eigen::MatrixXd _vel_goal_js_arm;
    //    Eigen::MatrixXd _vel_goal_js_base;


    //    /// Convergence goal for the velocity of an operational space (os) controller
    //    Eigen::MatrixXd _vel_goal_os_linear;
    //    Eigen::MatrixXd _vel_goal_os_angular;

    /// The default update rate
    int _update_rate;



    HybridAutomatonRBOParams()
    {
        num_dof_arm = 7;
        num_dof_base = 3;

        _index_vec_arm = Eigen::MatrixXd::Constant(num_dof_arm, 1, 0);
        for(int idx_arm=0; idx_arm<num_dof_arm; idx_arm++)
        {
            _index_vec_arm(idx_arm, 0) = idx_arm;
        }

        _index_vec_base = Eigen::MatrixXd::Constant(num_dof_base, 1, 0);
        for(int idx_base=0; idx_base<num_dof_base; idx_base++)
        {
            _index_vec_base(idx_base, 0) = idx_base+num_dof_arm;
        }

        max_vel_js_arm = Eigen::MatrixXd::Constant(num_dof_arm, 1, DEFAULT_MAX_VEL_JS_ARM);
        max_vel_js_base = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_MAX_VEL_JS_BASE);
        max_vel_js = _combineArmAndBase(max_vel_js_arm,max_vel_js_base);

        kp_js_arm = Eigen::MatrixXd::Constant(num_dof_arm, 1, DEFAULT_KP_JS_ARM);
        if(num_dof_arm == DEFAULT_NUM_DOF_ARM)
        {

            kp_js_arm << 300.0, 200.0, 150.0, 120.0, 10.0, 10.0, 10.0;
        }

        kp_js_base = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_KP_JS_BASE);
        kp_js = _combineArmAndBase(kp_js_arm, kp_js_base);

        kv_js_arm = Eigen::MatrixXd::Constant(num_dof_arm, 1, DEFAULT_KV_JS_ARM);
        if(num_dof_arm == DEFAULT_NUM_DOF_ARM)
        {
            kv_js_arm << 2.0, 4.0, 2.0, 1.2, 0.2, 0.3, 0.02;
        }
        kv_js_base = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_KV_JS_BASE);
        kv_js = _combineArmAndBase(kv_js_arm, kv_js_base);

        _kp_os_linear = Eigen::MatrixXd::Constant(3, 1, DEFAULT_KP_OS_LINEAR);
        _kp_os_angular = Eigen::MatrixXd::Constant(3, 1, DEFAULT_KP_OS_ANGULAR);
        _kv_os_linear = Eigen::MatrixXd::Constant(3, 1, DEFAULT_KV_OS_LINEAR);
        _kv_os_angular = Eigen::MatrixXd::Constant(3, 1, DEFAULT_KV_OS_ANGULAR);

        _kp_js_nakamura_arm = Eigen::MatrixXd::Constant(num_dof_arm, 1, DEFAULT_KP_JS_NAKAMURA_ARM);
        if(num_dof_arm == DEFAULT_NUM_DOF_ARM)
        {
            _kp_js_nakamura_arm << 30.0, 20.0, 15.0, 20.0, 10.0, 10.0, 10.0;
        }
        _kp_js_nakamura_base = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_KP_JS_NAKAMURA_BASE);

        _kv_js_nakamura_arm = Eigen::MatrixXd::Constant(num_dof_arm, 1, DEFAULT_KV_JS_NAKAMURA_ARM);
        if(num_dof_arm == DEFAULT_NUM_DOF_ARM)
        {
            _kv_js_nakamura_arm << 1.0, 2.0, 1.0, 0.4, 0.1, 0.1, 0.01;
        }
        _kv_js_nakamura_base = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_KV_JS_NAKAMURA_BASE);
        if(num_dof_base== DEFAULT_NUM_DOF_BASE)
        {
            _kv_js_nakamura_base << 10.0, 10.0, 2.0;
        }

        _joint_weights_nakamura_arm = Eigen::MatrixXd::Constant(num_dof_arm, 1, DEFAULT_JOINT_WEIGHTS_NAKAMURA_ARM);
        _joint_weights_nakamura_base = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_JOINT_WEIGHTS_NAKAMURA_BASE);
        _joint_weights_nakamura_base_no_rotation = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_JOINT_WEIGHTS_NAKAMURA_BASE);
        if(num_dof_base== DEFAULT_NUM_DOF_BASE)
        {
            _joint_weights_nakamura_base_no_rotation << DEFAULT_JOINT_WEIGHTS_NAKAMURA_BASE, DEFAULT_JOINT_WEIGHTS_NAKAMURA_BASE, DEFAULT_JOINT_WEIGHTS_NAKAMURA_BASE_LITTLE_MOTION;
        }
        _joint_weights_nakamura_base_little_motion = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_JOINT_WEIGHTS_NAKAMURA_BASE_LITTLE_MOTION);
        _home_config_js_arm = Eigen::MatrixXd::Constant(num_dof_arm, 1, DEFAULT_HOME_CONFIG_JS_ARM);
        if(num_dof_arm == DEFAULT_NUM_DOF_ARM)
        {
            _home_config_js_arm << 0.0, -0.14, 0.0, 2.18, 0.0, 0.2, -0.13;
        }
        _home_config_js_base = Eigen::MatrixXd::Constant(num_dof_base, 1, DEFAULT_HOME_CONFIG_JS_BASE);

        _pos_epsilon_js_arm  = DEFAULT_POS_EPSILON_JS_ARM;
        _pos_epsilon_js_base = DEFAULT_POS_EPSILON_JS_BASE;
        //pos_epsilon_js = _combineArmAndBase(_pos_epsilon_js_arm,_pos_epsilon_js_base);
        _vel_epsilon_js_arm = DEFAULT_VEL_EPSILON_JS_ARM;
        _vel_epsilon_js_base =  DEFAULT_VEL_EPSILON_JS_BASE;
        //vel_epsilon_js = _combineArmAndBase(_vel_epsilon_js_arm,_vel_epsilon_js_base);
        //        _vel_goal_js_arm = Eigen::MatrixXd::Constant(_num_dof_arm, 1, DEFAULT_VEL_GOAL_JS_ARM);
        //        _vel_goal_js_base = Eigen::MatrixXd::Constant(_num_dof_base, 1, DEFAULT_VEL_GOAL_JS_BASE);

        _pos_epsilon_os_linear =  DEFAULT_POS_EPSILON_OS_LINEAR;
        _pos_epsilon_os_angular =  DEFAULT_POS_EPSILON_OS_ANGULAR;
        _vel_epsilon_os_linear =  DEFAULT_VEL_EPSILON_OS_LINEAR;
        _vel_epsilon_os_angular =  DEFAULT_VEL_EPSILON_OS_ANGULAR;

        //        _vel_goal_os_linear = Eigen::MatrixXd::Constant(3, 1, DEFAULT_VEL_GOAL_OS_LINEAR);
        //        _vel_goal_os_angular =  Eigen::MatrixXd::Constant(3, 1, DEFAULT_VEL_GOAL_OS_ANGULAR);

        _max_vel_os_linear = DEFAULT_MAX_VEL_OS_LINEAR;
        _max_vel_os_angular = DEFAULT_MAX_VEL_OS_ANGULAR;

        _update_rate = DEFAULT_UPDATE_RATE;

        /// Grasp parameters
        gripper=SOFT_HAND;
        grasp_strength=4.0;
        grasp_type=0;

    }


    //    Eigen::MatrixXd max_vel_js_arm() const;
    //    void setMax_vel_js_arm(const Eigen::MatrixXd &max_vel_js_arm);

    //    Eigen::MatrixXd max_vel_js_base() const;
    //    void setMax_vel_js_base(const Eigen::MatrixXd &max_vel_js_base);

    //    Eigen::MatrixXd kp_js_arm() const;
    //    void setKp_js_arm(const Eigen::MatrixXd &kp_js_arm);

    //    Eigen::MatrixXd kp_js_base() const;
    //    void setKp_js_base(const Eigen::MatrixXd &kp_js_base);

    //    Eigen::MatrixXd kv_js_arm() const;
    //    void setKv_js_arm(const Eigen::MatrixXd &kv_js_arm);

    //    Eigen::MatrixXd kv_js_base() const;
    //    void setKv_js_base(const Eigen::MatrixXd &kv_js_base);

    //    Eigen::MatrixXd kp_os_linear() const;
    //    void setKp_os_linear(const Eigen::MatrixXd &kp_os_linear);

    //    Eigen::MatrixXd kp_os_angular() const;
    //    void setKp_os_angular(const Eigen::MatrixXd &kp_os_angular);

    //    Eigen::MatrixXd kv_os_linear() const;
    //    void setKv_os_linear(const Eigen::MatrixXd &kv_os_linear);

    //    Eigen::MatrixXd kv_os_angular() const;
    //    void setKv_os_angular(const Eigen::MatrixXd &kv_os_angular);

    //    Eigen::MatrixXd kp_js_nakamura_arm() const;
    //    void setKp_js_nakamura_arm(const Eigen::MatrixXd &kp_js_nakamura_arm);

    //    Eigen::MatrixXd kp_js_nakamura_base() const;
    //    void setKp_js_nakamura_base(const Eigen::MatrixXd &kp_js_nakamura_base);

    //    Eigen::MatrixXd kv_js_nakamura_arm() const;
    //    void setKv_js_nakamura_arm(const Eigen::MatrixXd &kv_js_nakamura_arm);

    //    Eigen::MatrixXd kv_js_nakamura_base() const;
    //    void setKv_js_nakamura_base(const Eigen::MatrixXd &kv_js_nakamura_base);

    //    Eigen::MatrixXd joint_weights_nakamura_arm() const;
    //    void setJoint_weights_nakamura_arm(const Eigen::MatrixXd &joint_weights_nakamura_arm);

    //    Eigen::MatrixXd joint_weights_nakamura_base() const;
    //    void setJoint_weights_nakamura_base(const Eigen::MatrixXd &joint_weights_nakamura_base);

    //    Eigen::MatrixXd joint_weights_nakamura_base_no_rotation() const;
    //    void setJoint_weights_nakamura_base_no_rotation(const Eigen::MatrixXd &joint_weights_nakamura_base_no_rotation);

    //    Eigen::MatrixXd joint_weights_nakamura_base_little_motion() const;
    //    void setJoint_weights_nakamura_base_little_motion(const Eigen::MatrixXd &joint_weights_nakamura_base_little_motion);

    //    Eigen::MatrixXd home_config_js_arm() const;
    //    void setHome_config_js_arm(const Eigen::MatrixXd &home_config_js_arm);

    //    Eigen::MatrixXd home_config_js_base() const;
    //    void setHome_config_js_base(const Eigen::MatrixXd &home_config_js_base);

    //    double pos_epsilon_js_arm() const;
    //    void setPos_epsilon_js_arm(const double &pos_epsilon_js_arm);

    //    double pos_epsilon_js_base() const;
    //    void setPos_epsilon_js_base(const double &pos_epsilon_js_base);

    //    double vel_epsilon_js_arm() const;
    //    void setVel_epsilon_js_arm(const double &vel_epsilon_js_arm);

    //    double vel_epsilon_js_base() const;
    //    void setVel_epsilon_js_base(const double &vel_epsilon_js_base);

    //    double pos_epsilon_os_linear() const;
    //    void setPos_epsilon_os_linear(const double &pos_epsilon_os_linear);

    //    double pos_epsilon_os_angular() const;
    //    void setPos_epsilon_os_angular(const double &pos_epsilon_os_angular);

    //    double vel_epsilon_os_linear() const;
    //    void setVel_epsilon_os_linear(const double &vel_epsilon_os_linear);

    //    double vel_epsilon_os_angular() const;
    //    void setVel_epsilon_os_angular(const double &vel_epsilon_os_angular);

};

/**
     * @brief A class to easily generate basic hybrid automata, control modes, control switches, jump conditions...
     *
     */
class HybridAutomatonRBOFactory : public HybridAutomatonAbstractFactory
{
public:

    typedef boost::shared_ptr<HybridAutomatonRBOFactory> Ptr;
    typedef boost::shared_ptr<const HybridAutomatonRBOFactory> ConstPtr;

    /**
         * @brief Default constructor
         *
         */
    HybridAutomatonRBOFactory();



    /**
         * @brief Destructor
         *
         */
    virtual ~HybridAutomatonRBOFactory();

    /**
         * @brief Copy constructor
         *
         * @param haf Object to make a copy from
         */
    HybridAutomatonRBOFactory(const HybridAutomatonRBOFactory& haf);

    /**
         * @brief Clone function
         *
         * @return HybridAutomatonRBOFactoryPtr Pointer to the generated clone
         */
    HybridAutomatonRBOFactoryPtr clone() const
    {
        return (HybridAutomatonRBOFactoryPtr(_doClone()));
    }

    /**
         * @brief Creates an initial HA that is immediately sent and that:
         * - Puts the robot in Gravity Compensation
         * - Switches off the Vacuum cleaner (if it is present)
         * - Opens the hand (if it is present)
         *
         * @param tool The tool used by the robot
         * @return ha::HybridAutomaton::Ptr Pointer to the generated HA
         */
    //    ha::HybridAutomaton::Ptr createInitialHybridAutomaton(const HybridAutomatonAbstractParams& params);

    /**
         * @brief Create an empty hybrid automaton which performs gravity compensation
         */
    ha::HybridAutomaton::Ptr createEmptyHybridAutomaton();

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GENERATION OF CONTROL SETS
    ///

    /**
         * @brief Create a control set for joint controllers
         *
         * @param ctrl The controller in the controlset
         * @return ha::ControlSet::Ptr The generated control set
         */
    ha::ControlSet::Ptr createControlSet(const HybridAutomatonAbstractParams& params,ha::Controller::Ptr ctrl);

    ha::ControlSet::Ptr createControlSet(const HybridAutomatonAbstractParams& params,const std::vector<ha::Controller::Ptr>& ctrls);

    /**
         * @brief Create a control set for task space controllers
         *
         * @param ctrl The controller in the controlset
         * @param move_base True if the control set should move both base and arm
         * @return ha::ControlSet::Ptr The generated control set
         */
    virtual ha::ControlSet::Ptr createTaskSpaceControlSet(const HybridAutomatonAbstractParams& params,
                                                   ha::Controller::Ptr ctrl,
                                                   bool move_base
                                                   );



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// GENERATION OF CONTROLLERS
    ///

    /**
     * @brief Create an interpolated joint space controller to move from the current robots position to a goal configuration
     *
     * @param name The controller name - must be unique within a hybrid automaton
     * @param goal the goal configuration
     * @param completion_time the desired time to arrive for the interpolator
     * @return ha::Controller::Ptr The generated controller
     */
    virtual ha::Controller::Ptr createGraspController(const HybridAutomatonAbstractParams& params,
                                                                         std::string name);

    virtual ha::Controller::Ptr createJointSpaceController(const HybridAutomatonAbstractParams& params,
                                                           std::string name,
                                                           const Eigen::MatrixXd &goal_js,
                                                           double completion_time,
                                                           bool goal_relative);

    virtual ha::Controller::Ptr createSubjointSpaceController(const HybridAutomatonAbstractParams& params,
                                                              std::string name,
                                                              const Eigen::MatrixXd& goal_js,
                                                              const Eigen::MatrixXd& index_vec,
                                                              bool is_relative);

    virtual ha::Controller::Ptr createBBSubjointSpaceController(const HybridAutomatonAbstractParams& params,
                                                                std::string name,
                                                                bool use_tf,
                                                                const std::string& topic_name,
                                                                const std::string& tf_parent,
                                                                const Eigen::MatrixXd& index_vec,
                                                                bool is_relative);
    /**
      * @brief Create an interpolated joint space controller to move from the current robots position to a goal configuration (only base)
      *
      * @param name The controller name - must be unique within a hybrid automaton
      * @param topic The topic where the goal for the controller is published
      * @param max_velocity The maximum velocity for the base
      * @return ha::Controller::Ptr The generated controller
      */
    virtual ha::Controller::Ptr createBBSubjointSpaceControllerBase(const HybridAutomatonAbstractParams& params,
                                                                    const std::string name,
                                                                    bool use_tf,
                                                                    const std::string& topic_name,
                                                                    const std::string& tf_parent,
                                                                    bool is_relative);



    virtual ha::Controller::Ptr createOperationalSpaceController(const HybridAutomatonAbstractParams& params,
                                                                 std::string name,
                                                                 const Eigen::MatrixXd &goal_op_translation,
                                                                 const Eigen::MatrixXd &goal_op_rot_matrix,
                                                                 double completion_time,
                                                                 bool is_relative);

    virtual ha::Controller::Ptr createOperationalSpaceController(const HybridAutomatonAbstractParams& params,
                                                                                    std::string name,
                                                                                    const Eigen::MatrixXd &goal_op_translation,
                                                                                    const Eigen::MatrixXd &goal_op_rot_matrix,
                                                                                    bool is_relative);
    /**
         * @brief Create an interpolated task space controller to move the end-effector from the current robots position to a goal frame given as a /tf frame
         *
         * The controller will continuously reinterpolate to the goal from the tf topic
         *
         * @param name The controller name - must be unique within a hybrid automaton
         * @param frame the target tf frame - the goal will be queried relative to /base_link
         * @param max_displacement_velocity the maximal end-effector translational velocity in m/s
         * @param max_rotational_velocity the maximal end-effector rotational velocity in rad/s
         */
    virtual ha::Controller::Ptr createBBOperationalSpaceController(const HybridAutomatonAbstractParams& params,
                                                                   std::string name,
                                                                   bool trajectory,
                                                                   bool use_tf,
                                                                   const std::string frame,
                                                                   const std::string parent_frame,
                                                                   bool is_relative);

    virtual void CreateGCCM(const HybridAutomatonAbstractParams& p,
                    const ha::ControlMode::Ptr& cm_ptr, const std::string& name);


    /**
     * @brief
     *
     * @param ha
     * @return std::string
     */
    std::string HybridAutomatonToString(ha::HybridAutomaton::ConstPtr ha);

protected:

    /**
         * @brief Performs the cloning operation (this solves some issues of inheritance and smart pointers)
         *
         * @return HybridAutomatonRBOFactory Pointer to the generated clone
         */
    virtual HybridAutomatonRBOFactory* _doClone() const
    {
        return (new HybridAutomatonRBOFactory(*this));
    }



//    /// Number of degrees of freedom of the arm
//    int _num_dof_arm;

//    /// Number of degrees of freedom of the base
//    int _num_dof_base;

//    /// Indices that define the convention for the joints of the arm and the base
//    std::string _index_str_base;
//    std::string _index_str_arm;
//    Eigen::MatrixXd _index_vec_base;
//    Eigen::MatrixXd _index_vec_arm;

//    /// Maximum joint space (js) velocity
//    Eigen::MatrixXd _max_vel_js_arm;
//    Eigen::MatrixXd _max_vel_js_base;

//    /// Joint space (js) gains
//    Eigen::MatrixXd _kp_js_arm;
//    Eigen::MatrixXd _kp_js_base;
//    Eigen::MatrixXd _kv_js_arm;
//    Eigen::MatrixXd _kv_js_base;

//    /// Operational space gains (3x orientation + 3x position)
//    Eigen::MatrixXd _kp_os_linear;
//    Eigen::MatrixXd _kp_os_angular;
//    Eigen::MatrixXd _kv_os_linear;
//    Eigen::MatrixXd _kv_os_angular;

//    /// Joint space integration gains for operational space Nakamura control set
//    Eigen::MatrixXd _kp_js_nakamura_arm;
//    Eigen::MatrixXd _kp_js_nakamura_base;
//    Eigen::MatrixXd _kv_js_nakamura_arm;
//    Eigen::MatrixXd _kv_js_nakamura_base;

//    /// Weights of each joint for operational space Nakamura control set
//    Eigen::MatrixXd _joint_weights_nakamura_arm;
//    Eigen::MatrixXd _joint_weights_nakamura_base;
//    Eigen::MatrixXd _joint_weights_nakamura_base_no_rotation;
//    Eigen::MatrixXd _joint_weights_nakamura_base_little_motion;

//    /// Home configuration - usually a good initial position to begin the interaction and/or a safe
//    /// position to return to
//    Eigen::MatrixXd _home_config_js_arm;
//    Eigen::MatrixXd _home_config_js_base;

//    /// Maximum joint space (os) velocity
//    double _max_vel_os_linear;
//    double _max_vel_os_angular;

//    /// Convergence radius for the position of a joint space (js) controller
//    double _pos_epsilon_js_arm;
//    double _pos_epsilon_js_base;

//    /// Convergence radius for the velocity of a joint space (js) controller
//    double _vel_epsilon_js_arm;
//    double _vel_epsilon_js_base;

//    /// Convergence goal for the velocity of a joint space (js) controller
//    Eigen::MatrixXd _vel_goal_js_arm;
//    Eigen::MatrixXd _vel_goal_js_base;

//    /// Convergence radius of an operational space (os) controller
//    double _pos_epsilon_os_linear;
//    double _pos_epsilon_os_angular;

//    /// Convergence radius for the velocity of an operational space (os) controller
//    double _vel_epsilon_os_linear;
//    double _vel_epsilon_os_angular;

//    /// Convergence goal for the velocity of an operational space (os) controller
//    Eigen::MatrixXd _vel_goal_os_linear;
//    Eigen::MatrixXd _vel_goal_os_angular;

//    /// The default update rate
//    int _update_rate;
};

}

#endif
