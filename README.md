# btSDK
btSDK - game development tools.
Designed to be flexible, fast & lightweight.
Engine structure allows to use project-specific editors & tools.

SDK contains most common tools:
 - texture editor (atlas, compression, effects, convertion, etc);
 - material editor (shader, texture);
 - scene editor (environment, scripts, integrations);
 - audio (sfx);
 - font editor (bitmap & other formats);
 - builder (compile, runt tests, deploy);
 - localization editor;
 - script editor (with visual editing support);

SDK depends on sub-modules:
 - engine:
  - core;
  - ecs;
  - render:
   - gl;
   - dx;
   - vk;
  - platform:
   - android;
   - windows;
   - linux;
  - net;
  - assets:
   - assimp;
   - soil;
  - audio:
   - opensl;
  - threading:
   - windows;
   - posix;
  - input:
   - android;
   - sdl;
   - xinput;
  - particles;
  - physics:
   - box2d;
   - bullet;
  - & many others;
