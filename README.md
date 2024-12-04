# Example01


할일
-------------  
1. world 생성 및 main Scene 옮기기 [X] 
2. movement component 생성 및 이동 관련 함수 변수들 옮기기 [x] 
3. animcontroller 정리 [x] 
4. MessageProc[in IActorComponent] 완성 [ ] 
5.  Animal component 완성 [x]   
6.  goal 만들고 움직이는 ai 구현[ ]
7.  소 도축 하기
- [ ]  단일 목적 및 복합 목적 디자인
- [ ]  physicsBody 생성
8. 실시간 서버 정보 전달 (axmol 개별 클라이언트 소켓 생성 연결)[x]
1. 
9. 무한맵 구현[x]

10.WASD입력을 받는 무브먼트 구현(동시에 누르면 대각이동)[x]


11. audio엔진 습득
 1. [ ] 서버에서도 따로 받는 상태 구현
12. 투사체 구현및 여러 종류의 투사체를 발사 할 수 있게 만들기
 1. [ ] weaponcomponent 제작
 1. [ ] vector weaponlist 를 actor에서 업데이트로 구현 가지고 있는 무기들을 나열해서 독자적인 투사체유닛들을 생성하고 발사함

13.자동 조준,투사체 물리법칙 구현[ ]



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



피직스를 쓸경우
엑터의 겟포지션을 호출할땐 씬컴포넌트의 노드의 포지션을 리턴한다.
movementcomnent제거 및 씬컴포넌트에서 엑터의 포지션을 받는게 아니라 변경시킨다.
