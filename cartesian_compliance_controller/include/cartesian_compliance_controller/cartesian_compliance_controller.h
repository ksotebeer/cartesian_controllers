////////////////////////////////////////////////////////////////////////////////
// Copyright 2019 FZI Research Center for Information Technology
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*!\file    cartesian_compliance_controller.h
 *
 * \author  Stefan Scherzinger <scherzin@fzi.de>
 * \date    2017/07/27
 *
 */
//-----------------------------------------------------------------------------

#ifndef CARTESIAN_COMPLIANCE_CONTROLLER_H_INCLUDED
#define CARTESIAN_COMPLIANCE_CONTROLLER_H_INCLUDED

// Project
#include <cartesian_controller_base/cartesian_controller_base.h>
#include <cartesian_motion_controller/cartesian_motion_controller.h>
#include <cartesian_force_controller/cartesian_force_controller.h>

// Dynamic reconfigure
#include <dynamic_reconfigure/server.h>
#include <cartesian_compliance_controller/ComplianceControllerConfig.h>

namespace cartesian_compliance_controller
{

template <class HardwareInterface>
class CartesianComplianceController
: public cartesian_motion_controller::CartesianMotionController<HardwareInterface>
, public cartesian_force_controller::CartesianForceController<HardwareInterface>
{
  public:
    CartesianComplianceController();

    bool init(HardwareInterface* hw, ros::NodeHandle& nh);

    void starting(const ros::Time& time);

    void stopping(const ros::Time& time);

    void update(const ros::Time& time, const ros::Duration& period);

    typedef cartesian_controller_base::CartesianControllerBase<HardwareInterface> Base;
    typedef cartesian_motion_controller::CartesianMotionController<HardwareInterface> MotionBase;
    typedef cartesian_force_controller::CartesianForceController<HardwareInterface> ForceBase;

  private:
    ctrl::Vector6D        computeComplianceError();

    ctrl::Matrix6D        m_stiffness;
    std::string           m_compliance_ref_link;

    // Dynamic reconfigure for stiffness
    typedef cartesian_compliance_controller::ComplianceControllerConfig
      ComplianceConfig;

    void dynamicReconfigureCallback(ComplianceConfig& config, uint32_t level);

    boost::shared_ptr<dynamic_reconfigure::Server<ComplianceConfig> > m_dyn_conf_server;
    dynamic_reconfigure::Server<ComplianceConfig>::CallbackType m_callback_type;
};

}

#include <cartesian_compliance_controller/cartesian_compliance_controller.hpp>

#endif
