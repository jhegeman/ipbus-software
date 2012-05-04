%%% ===========================================================================
%%% @author Robert Frazier
%%%
%%% @since May 2012
%%%
%%% @doc Application metadata. List of modules, the "starting point" module
%%%      (controlhub_app), and application dependencies, etc, etc.  This file
%%%      is an OTP requirement.
%%% @end
%%% ===========================================================================
{application, controlhub,
 [{description, "Control Hub: multi-client packet routing for IPbus/UDP hardware"},
   {vsn, "1.1.0"},
   {modules, [ch_device_client_registry,
              ch_device_client,
              ch_stats,
              ch_tcp_listerner,
              ch_transaction_manager,
              ch_utils]},
   {registered, [ch_device_client_registry,
                 ch_stats,
                 ch_sup]},
   {applications, [kernel, stdlib]},
   {mod, {controlhub_app, []}},
 ]
}