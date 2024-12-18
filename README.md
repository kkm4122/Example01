# Example01


완수
-------------  
    1. world 생성 및 main Scene 옮기기 [X] 
    2. movement component 생성 및 이동 관련 함수 변수들 옮기기 [x] 
    3. animcontroller 정리 [x] 
    4.  Animal component 완성 [x]   
    5. 실시간 서버 정보 전달 (axmol 개별 클라이언트 소켓 생성 연결)[x]
    6. 무한맵 구현[x]
    7.WASD입력을 받는 무브먼트 구현(동시에 누르면 대각이동)[x]
    8.자동 조준,투사체 물리법칙 구현[x]
    9. 조준 메커니즘 설정
    - [x] 메인씬에서 충돌체크
    - [x] 센서 컴포넌트 및 월드에 센서리스트-> 센서 컴포넌트가 자체적으로 리스트를 가짐
    - [x] 리스트 검색 및 가장 가까운 거리 체크
    10. Weapon
    - [x] weaponcomponent 제작
    - [x] vector weaponlist 를 actor에서 업데이트로 구현 가지고 있는 무기들을 나열해서 독자적인 투사체유닛들을 생성하고 발사함      
   
    11. world actorlist 수정   [x]
   
    
    
    
    
    
    

    
    
    
    
   할일
------------- 

    1. MessageProc[in IActorComponent] 완성 [ ] 
    2.  goal 만들고 움직이는 ai 구현[ ]

    3.  소 도축 하기
   - [ ]단일 목적 및 복합 목적 디자인
   - [x]  physicsBody 생성
  
    4. 투사체 구현및 여러 종류의 투사체를 발사 할 수 있게 만들기
   - [x]튕기는 투사체 구현
   - [ ]관통 투사체 구현
   - [x]멀티샷 구현
   
    5. 게임시스템 구현
   - [ ] 레벨 및 ItemActor
   - [ ] 캐릭터 스텟 및 정보창 구현
   - [ ] FairyGui로 리소스 추가 및 ui 구현


    6. ImGuI 추가 
    
    7. audio엔진 습득
   
    8. MovementCompnent 수정 physicsbody에 맞게

    9. 몬스터 웨이브 구현

    10. get Physics node 추가 설정 및 쉐이프를 통한 피직스 바디 얻어오기



교육자료
-------------  

1.[마크다운(.md) 사용법][markdown]

[markdown]:https://gist.github.com/ihoneymon/652be052a0727ad59601

2.[string 클래스][string]

[string]:https://blockdmask.tistory.com/338

3.[cocos2d API Reference][cocos doc]

[cocos doc]:https://docs.cocos2d-x.org/api-ref/cplusplus/v4x/

4.[Axmol API Reference      ][ax doc]

[ax doc]:https://axmol.dev/manual/latest/

5.[cocos Physics body sprite][physics]

[physics]:https://m.blog.naver.com/game_studyz/220886309728?recommendTrackingCode=2

6.[cocos포럼][coocs]

[coocs]:https://forum.cocosengine.org/
physicsBody를 쓸경우
Actor의 mPosition을 호출할땐 Scenecomp의 rootNode의 Position을 리턴한다.
movementcomnent제거 및 Scenecomp에서 Actor의 mPosition을 받는게 아니라 변경시킨다.
