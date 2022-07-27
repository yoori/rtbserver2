/*
 * This file is part of the RTBServer distribution (https://github.com/yoori/rtbserver2).
 * RTBServer is DSP server that allow to bid (see RTB auction) targeted ad
 * via RTB protocols (OpenRTB, Google AdExchange, Yandex RTB)
 *
 * Copyright (c) 2017 Yuri Kuznecov <yuri.kuznecov@gmail.com>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the
 * GNU Lesser General Public License (version 3)
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _AUTOTESTS_COMMONS_ADMINS_SIMPLEADMINS_HPP
#define _AUTOTESTS_COMMONS_ADMINS_SIMPLEADMINS_HPP

#include "Admins.hpp"
#include <tests/AutoTests/Commons/BaseUnit.hpp>

namespace AutoTest
{

  /**
   * @class ChannelMatchLog
   * @brief Log ChannelMatchAdmin output.
   *
   * Execute ChannelMatchAdmin command and log it's output without examination.
   */
  class ChannelMatchLog:  
    public ShellCmd  
  {  
  public:

    /**
     * @brief Make ChannelMatchAdmin call string.
     * @param address manager object address.
     * @param trigger
     * @param service.
     */
    void
    make_cmd(
      const char* address,      
      const char* trigger,      
      ChannelSrv service);

    /**
     * @brief Constructors.
     *
     * @param address manager object address.
     * @param trigger
     * @param service.
     */
    ChannelMatchLog(      
      const char* address,      
      const char* trigger,      
      ChannelSrv service = ChannelManagerController);
    
    ChannelMatchLog(      
      const std::string& address,      
      const char* trigger,      
      ChannelSrv service = ChannelManagerController);
    
    ChannelMatchLog(      
      const char* address,      
      const std::string& trigger,      
      ChannelSrv service = ChannelManagerController);
    
    ChannelMatchLog(      
      const std::string& address,      
      const std::string& trigger,      
      ChannelSrv service = ChannelManagerController);
  };

  /**
   * @class UserInfoAdminLog
   * @brief Log UserInfoAdmin output.
   *
   * Execute UserInfoAdmin 'print' command and log it's output without examination.
   */
  class UserInfoAdminLog:
    public ShellCmd
  {
  protected:

    /**
     * @brief Make UserInfoAdmin call string.
     * @param address manager object address.
     * @param command
     * @param UUID.
     */
    void
    make_cmd (
      const char* address,
      const char* uuid,
      UserInfoSrv service,
      bool temp);
                       
  public:

    /**
     * @brief Constructor.
     *
     * Creates UserInfoAdminLog object and initialize it.
     * @param address manager object address.
     * @param command
     * @param UUID
     */
    UserInfoAdminLog(
      const char* address,
      const char* uuid,
      UserInfoSrv service = UserInfoManager,
      bool temp = false);
  };

  /**
   * @class DeleteOldUserProfiles
   * @brief Delete old user profiles from UserInfoManager.
   *
   * Execute UserInfoAdmin 'delete-old-profiles' command.
   */
  class DeleteOldUserProfiles:
    public ShellCmd
  {
  protected:

    /**
     * @brief Makes UserInfoAdmin call string.
     * @param address manager object address.
     */
    void make_cmd(
      const char* address);

  public:

    static void
    execute(BaseUnit* test)
      /*throw(eh::Exception)*/;

    /**
     * @brief Constructor.
     * @param manager object address.
     */
    DeleteOldUserProfiles(const char* address);
  };


  /**
   * @class ClearExpiredProfiles
   * @brief Delete expired user profiles from RequestInfoManager.
   *
   * Execute RequestInfoAdmin 'clear-expired' command.
   */
  class ClearExpiredProfiles:
    public ShellCmd
  {
  protected:

    /**
     * @brief Makes RequestInfoAdmin call string.
     * @param RequestInfoManager address.
     */
    void make_cmd(
      const char* address);

  public:

    static void
    execute(BaseUnit* test)
      /*throw(eh::Exception)*/;

    /**
     * @brief Constructor.
     * @param RequestInfoManager address.
     */
    ClearExpiredProfiles(const char* address);
    
  };

  /**
   * @class UpdateStats
   * @brief Update CampaignServer's stat.
   *
   * Execute CampaignAdmin 'update_stat' command.
   */
  class UpdateStats:
    public ShellCmd
  {
  protected:

    /**
     * @brief Makes CampaignAdmin call string.
     * @param CampaignServer address.
     */
    void make_cmd(
      const char* address);

  public:

    static void
    execute(BaseUnit* test)
      /*throw(eh::Exception)*/;

    /**
     * @brief Constructor.
     * @param CampaignServer address.
     */
    UpdateStats(const char* address);
    
  };

  /**
   * @class DailyProcess
   * @brief Run daily processing on expression-matcher.
   *
   * Execute ExpressionMatchAdmin 'daily-process' command.
   */
  class DailyProcess:
    public ShellCmd
  {
  protected:

    /**
     * @brief Makes ExpressionMatchAdmin call string.
     * @param ExpressionMatcher address.
     */
    void make_cmd(
      const char* address);

  public:

    static void
    execute(BaseUnit* test)
      /*throw(eh::Exception)*/;

    /**
     * @brief Constructor.
     * @param ExpressionMatcher address.
     */
    DailyProcess(
      const char* address);

  };

  /**
   * @class CopyCmd
   * @brief class to copy files
   */
  class CopyCmd:
    protected ShellCmd
  {
    static const char* DEFAULT_EXECUTOR_;
  public:
    /**
     * @brief Constructors.
     *
     * @param from source to copy
     * @param to distancion to copy
     */
    CopyCmd(
      const std::string& from,
      const std::string& to);

    /**
     * @brief Executes command
     */
    void exec();
  };  

  class MoveCmd:
    protected ShellCmd
  {
    static const char* DEFAULT_EXECUTOR_;
  public:
    /**
     * @brief Constructors.
     *
     * @param from source to move
     * @param to distancion to move
     */
    MoveCmd(
      const std::string& from,
      const std::string& to);

    /**
     * @brief Executes command
     */
    void exec();
  };
}


#endif  // _AUTOTESTS_COMMONS_ADMINS_SIMPLEADMINS_HPP
