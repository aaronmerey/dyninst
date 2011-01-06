#if !defined(EVENTTYPE_H_)
#define EVENTTYPE_H_

namespace Dyninst {
namespace ProcControlAPI {

class EventType
{
 public:
   static const int Error               = -1;
   static const int Unset               = 0;
   static const int Exit                = 1;
   static const int Crash               = 2;
   static const int Fork                = 3;
   static const int Exec                = 4;
   static const int UserThreadCreate    = 5;
   static const int LWPCreate           = 6;
   static const int ThreadDestroy       = 7;
   static const int UserThreadDestroy   = 8;
   static const int LWPDestroy          = 9;
   static const int Stop                = 10;
   static const int Signal              = 11;
   static const int LibraryLoad         = 12;
   static const int LibraryUnload       = 13;
   static const int Bootstrap           = 14;
   static const int Breakpoint          = 15;
   static const int RPC                 = 16;
   static const int SingleStep          = 17;
   static const int Library             = 18;

   //These aren't completely real events.  They can have callbacks registered, but won't be delivered.
   // Instead, a real event will be delivered to their callback.  E.g, a callback registered for 
   // Terminate will actually get Exit or Crash events.
   static const int Terminate           = 400;
   static const int ThreadCreate        = 401;

   //Users do not recieve CBs for the below event types--ProcControlAPI internal
   static const int InternalEvents      = 500;
   static const int BreakpointClear     = 500;
   static const int RPCInternal         = 501;
   static const int Async               = 502;
   static const int ChangePCStop        = 503; // Used for bug_freebsd_change_pc
   static const int Detached            = 504;
   static const int IntBootstrap        = 505;

   //Users should define their own events at this value or higher.
   static const int MaxProcCtrlEvent    = 1000;
   typedef int Code;

   typedef enum {
      Pre = 0,
      Post,
      None,
      Any
   } Time;

   Code code() const { return ecode; }
   Time time() const { return etime; }

   EventType(Code e) : ecode(e), etime(Any) {}
   EventType(Time t, Code e) : ecode(e), etime(t) {}
   EventType() : ecode(Unset), etime(None) {}
   
   std::string name() const;
 protected:
   Code ecode;
   Time etime;
};

struct eventtype_cmp
{
   bool operator()(const EventType &a, const EventType &b)
   {
      if (a.code() < b.code()) 
         return true;
      if (a.code() > b.code())
         return false;
      return ((int) a.time() < (int) b.time());
   }
};

}
}

#endif
