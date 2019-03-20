#include "gyftietoken.hpp"


ACTION gyftietoken::setcount (uint32_t count)
{
    counter_table counter(get_self(), get_self().value);
    Counter c ;
    c.account_count = count;
    counter.set (c, get_self());
}

ACTION gyftietoken::miggyftss1 ()
{
    require_auth (get_self());
    gyft_table g_t (get_self(), get_self().value);
    auto g_itr = g_t.begin();

    tgyft_table tg_t (get_self(), get_self().value);
    
    while (g_itr != g_t.end()) {
        tg_t.emplace (get_self(), [&] (auto& tg) {
            tg.gyft_id = g_itr->gyft_id;
            tg.gyfter = g_itr->gyfter;
            tg.gyftee = g_itr->gyftee;
            tg.gyfter_issue = g_itr->gyfter_issue;
            tg.gyftee_issue = g_itr->gyftee_issue;
            tg.relationship = g_itr->relationship;
            tg.notes = g_itr->notes;
            tg.gyft_date = g_itr->gyft_date;
            tg.likes = g_itr->likes;            
        });
       g_itr++;
    }

    g_itr = g_t.begin();
    while (g_itr != g_t.end()) {
        g_itr = g_t.erase(g_itr);
    }
}


ACTION gyftietoken::miggyftss2 ()
{
    require_auth (get_self());
    tgyft_table tg_t (get_self(), get_self().value);
    auto tg_itr = tg_t.begin();

    gyft_table g_t (get_self(), get_self().value);
    
    while (tg_itr != tg_t.end()) {
        g_t.emplace (get_self(), [&] (auto& g) {
            g.gyft_id = tg_itr->gyft_id;
            g.gyfter = tg_itr->gyfter;
            g.gyftee = tg_itr->gyftee;
            g.gyfter_issue = tg_itr->gyfter_issue;
            g.gyftee_issue = tg_itr->gyftee_issue;
            g.relationship = tg_itr->relationship;
            g.notes = tg_itr->notes;
            g.gyft_date = tg_itr->gyft_date;
            g.likes = tg_itr->likes;            
        });
        tg_itr++;
    }

    tg_itr = tg_t.begin();
    while (tg_itr != tg_t.end()) {
        tg_itr = tg_t.erase(tg_itr);
    }
}

// ACTION gyftietoken::copybal1 ()
// {
//     require_auth ("zombiejigsaw"_n);

//     config_table config (get_self(), get_self().value);
//     Config c = config.get();

//     profile_table p_t (get_self(), get_self().value);
//     tempacct_table t_t (get_self(), get_self().value);
//     symbol gft_symbol = symbol{symbol_code(GYFTIE_SYM_STR.c_str()), GYFTIE_PRECISION};

//     accounts a_t (get_self(), c.gftorderbook.value);
//     auto a_itr = a_t.find (gft_symbol.code().raw());

//     t_t.emplace (get_self(), [&](auto &t) {
//         t.account = c.gftorderbook;
//         t.balance = a_itr->balance;
//     });

//     a_t = accounts (get_self(), c.gyftie_foundation.value);
//     a_itr = a_t.find (gft_symbol.code().raw());

//     t_t.emplace (get_self(), [&](auto &t) {
//         t.account = c.gyftie_foundation;
//         t.balance = a_itr->balance;
//     });

//     auto p_itr = p_t.begin();
//     while (p_itr != p_t.end()) {
//         a_t = accounts (get_self(), p_itr->account.value);
//         a_itr = a_t.find (gft_symbol.code().raw());

//         t_t.emplace (get_self(), [&](auto& t) {
//             t.account = p_itr->account;
//             t.balance = a_itr->balance;
//         });
//         p_itr++;
//     }
// }

// ACTION gyftietoken::remaccounts ()
// {
//     require_auth ("zombiejigsaw"_n);

//     config_table config (get_self(), get_self().value);
//     Config c = config.get();    
    
//     symbol gft_symbol = symbol{symbol_code(GYFTIE_SYM_STR.c_str()), GYFTIE_PRECISION};

//     accounts a_t (get_self(), c.gftorderbook.value);
//     auto a_itr = a_t.find (gft_symbol.code().raw());
//     a_t.erase (a_itr);

//     a_t = accounts (get_self(), c.gyftie_foundation.value);
//     a_itr = a_t.find (gft_symbol.code().raw());
//     a_t.erase (a_itr);

//     profile_table p_t (get_self(), get_self().value);

//     auto p_itr = p_t.begin();
//     while (p_itr != p_t.end()) {
//         accounts a_t (get_self(), p_itr->account.value);
//         auto a_itr = a_t.find (gft_symbol.code().raw());
//         a_t.erase (a_itr);
//         p_itr++;
//     }
// }

// ACTION gyftietoken::repopaccts ()
// {
//     require_auth ("zombiejigsaw"_n);
  
//     tempacct_table t_t (get_self(), get_self().value);
//     symbol gft_symbol = symbol{symbol_code(GYFTIE_SYM_STR.c_str()), GYFTIE_PRECISION};

//     auto t_itr = t_t.begin();
//     while (t_itr != t_t.end()) {
//         accounts a_t (get_self(), t_itr->account.value);
//         a_t.emplace (get_self(), [&](auto &a) {
//             a.balance = t_itr->balance;
//         });
//         t_itr++;
//     }
// }

// ACTION gyftietoken::remtemp () 
// {
//     require_auth ("zombiejigsaw"_n);
//     tempacct_table t_t (get_self(), get_self().value);
//     auto t_itr = t_t.begin();
//     while (t_itr != t_t.end()) {
//         t_itr = t_t.erase (t_itr);
//     }
// }

ACTION gyftietoken::setconfig (name token_gen,
                                name gftorderbook,
                                name gyftie_foundation)
{
    require_auth (get_self());
        
    config_table config (get_self(), get_self().value);
    Config c;
    c.token_gen = token_gen;
    c.gftorderbook = gftorderbook;
    c.gyftie_foundation = gyftie_foundation;
    c.paused = PAUSED;
    config.set (c, get_self());
}

ACTION gyftietoken::pause () 
{
    require_auth (get_self());
    config_table config (get_self(), get_self().value);
    Config c = config.get();
    c.paused = PAUSED;
    config.set (c, get_self());
}

ACTION gyftietoken::unpause () 
{
    require_auth (get_self());
    config_table config (get_self(), get_self().value);
    Config c = config.get();
    c.paused = UNPAUSED;
    config.set (c, get_self());
}

ACTION gyftietoken::setcounter (uint64_t account_count)
{
    require_auth (get_self());

    counter_table counter (get_self(), get_self().value);
    Counter c;
    c.account_count = account_count;
    counter.set(c, get_self());
}

ACTION gyftietoken::delconfig () 
{
    require_auth (get_self());
    config_table config (get_self(), get_self().value);
    config.remove();
}

// ACTION gyftietoken::setvalidator (name account, uint8_t active_validator)
// {
//     require_auth (account);
//     eosio_assert (is_tokenholder (account), "Account is not a GFT token holder.");
//     eosio_assert (! is_paused(), "Contract is paused." );

//     profile_table p_t (get_self(), get_self().value);
//     auto p_itr = p_t.find (account.value);
//     eosio_assert (p_itr != p_t.end(), "Account not found.");

//     p_t.modify (p_itr, get_self(), [&](auto &p) {
//         p.active_validator = active_validator;
//     });
// }

ACTION gyftietoken::nchallenge (name challenger_account, name challenged_account, string note)
{
    require_auth (challenger_account);
    permit_account(challenger_account);
    eosio_assert (challenger_account != challenged_account, "Account cannot challenge itself.");
    eosio_assert (is_tokenholder (challenger_account), "Challenger is not a GFT token holder.");
    eosio_assert (is_tokenholder (challenged_account), "Challenged account is not a GFT token holder.");
    eosio_assert (! is_paused(), "Contract is paused." );

    challenge_table c_t (get_self(), get_self().value);
    auto challenged_index = c_t.get_index<"bychallenged"_n>();
    auto c_itr = challenged_index.find(challenged_account.value);

    if (c_itr != challenged_index.end()) {
        while (c_itr != challenged_index.end()) {
            if (c_itr->status != VALIDATED) {
                string new_challenge_note { "New challenge from: " + name {challenged_account}.to_string() };
                challenged_index.modify (c_itr, get_self(), [&] (auto &c) {
                    c.challenge_notes.push_back (new_challenge_note);
                    c.challenge_notes.push_back (note);
                });
            }
            c_itr++;
        }        
    } else {
        c_t.emplace (get_self(), [&](auto &c) {
            c.challenge_id = c_t.available_primary_key();
            c.challenged_account = challenged_account;
            c.challenger_account = challenger_account;
            c.challenged_time = now();
            c.challenge_notes.push_back (note);
            c.status = NEW_CHALLENGE;
        });
    }
}

ACTION gyftietoken::addcidnote (name scribe, uint64_t challenge_id, string note)
{
    require_auth (scribe);
    eosio_assert (is_tokenholder (scribe), "Scribe is not a GFT token holder.");
    eosio_assert (! is_paused(), "Contract is paused." );

    challenge_table c_t (get_self(), get_self().value);
    auto c_itr = c_t.find (challenge_id);
    eosio_assert (c_itr != c_t.end(), "Challenge ID not found.");

    c_t.modify (c_itr, get_self(), [&] (auto &c) {
        c.challenge_notes.push_back (note);
    });
}

ACTION gyftietoken::addcnote (name scribe, name challenged_account, string note)
{
    require_auth (scribe);
    eosio_assert (is_tokenholder (scribe), "Scribe is not a GFT token holder.");
    eosio_assert (! is_paused(), "Contract is paused." );

    challenge_table c_t (get_self(), get_self().value);
    auto challenged_index = c_t.get_index<"bychallenged"_n>();
    auto c_itr = challenged_index.begin();
    eosio_assert (c_itr != challenged_index.end(), "Account has not been challenged.");
    
    while (c_itr != challenged_index.end()) {
        if (c_itr->status != VALIDATED) {
            challenged_index.modify (c_itr, get_self(), [&] (auto &c) {
                c.challenge_notes.push_back (note);
            });
        }
        c_itr++;
    }
}

ACTION gyftietoken::validate (name validator, name account, string idhash, string id_expiration)
{
    permit_account(validator);
    permit_validator(validator, account);
    require_auth (validator);
    eosio_assert (is_tokenholder (validator), "Validator is not a GFT token holder.");
    eosio_assert (! is_paused(), "Contract is paused." );

    profile_table p_t (get_self(), get_self().value);
    auto p_itr = p_t.find (account.value);
    eosio_assert (p_itr != p_t.end(), "Account not found.");

    challenge_table c_t (get_self(), get_self().value);
    
    if (p_itr->idhash.compare(idhash) == 0) {
        challenge_table c_t (get_self(), get_self().value);
        auto challenged_index = c_t.get_index<"bychallenged"_n>();
        auto c_itr = challenged_index.begin();
        eosio_assert (c_itr != challenged_index.end(), "Account has not been challenged.");
        string note { "Validated by " + name {validator}.to_string() };

        while (c_itr != challenged_index.end()) {
            challenged_index.modify (c_itr, get_self(), [&] (auto &c) {
                c.status = VALIDATED;
                c.challenge_notes.push_back (note);
                c.validated_time = now();
            });
            c_itr++;
        }
    } else {
        string note { "Validation failed with " + idhash };
        addcnote (validator, account, note);
    }
}

ACTION gyftietoken::addrating (name rater, name ratee, uint8_t rating)
{
    permit_account(rater);
    availrating_table a_t (get_self(), rater.value);
    auto a_itr = a_t.find (ratee.value);
    eosio_assert (a_itr != a_t.end(), "Account is not available for rating.");
    eosio_assert (has_auth (rater), "Only eligible rater can add a rating.");
    eosio_assert (a_itr->rate_deadline >= now(), "Deadline to rate account has passed.");

    profile_table p_t (get_self(), get_self().value);
    auto p_itr = p_t.find (ratee.value);
    eosio_assert (p_itr != p_t.end(), "Account to rate is not found.");
    
    p_t.modify (p_itr, get_self(), [&](auto &p) {
        p.rating_count++;
        p.rating_sum += rating;
    });
    
    a_t.erase (a_itr);
}

ACTION gyftietoken::removeprop (uint64_t proposal_id) 
{
    proposal_table p_t (get_self(), get_self().value);
    auto p_itr = p_t.find(proposal_id);
    eosio_assert (p_itr != p_t.end(), "Proposal ID is not found.");

    eosio_assert (  has_auth (get_self()) || 
                    has_auth (p_itr->proposer) ||
                    has_auth ("danielflora3"_n) ||
                    has_auth ("zombiejigsaw"_n),    
        "Permission denied - only Gyftie signatory or proposer can remove a proposal.");

    p_t.erase (p_itr);
}

ACTION gyftietoken::propose (name proposer,
                                string notes) 
{
    permit_account(proposer);
    eosio_assert (! is_paused(), "Contract is paused." );
    require_auth (proposer);
    eosio_assert (is_tokenholder (proposer), "Proposer is not a GFT token holder.");

    proposal_table p_t (get_self(), get_self().value);

    p_t.emplace (proposer, [&](auto &p) {
        p.proposal_id   = p_t.available_primary_key();
        p.created_date  = now();
        p.proposer      = proposer;
      //  p.new_token_gen = token_gen;
        p.notes         = notes;
        p.votes_for     = 0;
        p.votes_against = 0;
        p.expiration_date   = now() + (60 * 60 * 24 * 30);  // 30 days
    });
}

ACTION gyftietoken::votefor (name voter,
                            uint64_t proposal_id) 
{
    eosio_assert (! is_paused(), "Contract is paused." );

    require_auth (voter);
    eosio_assert (is_tokenholder (voter), "Voter is not a GFT token holder.");
    
    proposal_table p_t (get_self(), get_self().value);
    auto p_itr = p_t.find (proposal_id);
    eosio_assert (now() <= p_itr->expiration_date, "Proposal has expired.");

    auto voter_for_itr = std::find (p_itr->voters_for.begin(), p_itr->voters_for.end(), voter);
    eosio_assert (voter_for_itr == p_itr->voters_for.end(), "User has already voted.");

    auto voter_against_itr = std::find (p_itr->voters_against.begin(), p_itr->voters_against.end(), voter);
    eosio_assert (voter_against_itr == p_itr->voters_against.end(), "User has already voted.");

    // uint32_t votes = 0;

    p_t.modify (p_itr, get_self(), [&](auto &p) {
        p.votes_for++;
        p.voters_for.push_back (voter);
    });

    // config_table config (get_self(), get_self().value);
    // auto c = config.get();

    // if (votes > (c.account_count / 2)) {
    //     c.token_gen = p_itr->new_token_gen;
    //     config.set (c, get_self());
    // }
}

ACTION gyftietoken::voteagainst (name voter,
                            uint64_t proposal_id) 
{
    eosio_assert (! is_paused(), "Contract is paused." );

    require_auth (voter);
    eosio_assert (is_tokenholder (voter), "Voter is not a GFT token holder.");
    
    proposal_table p_t (get_self(), get_self().value);
    auto p_itr = p_t.find (proposal_id);
    eosio_assert (now() <= p_itr->expiration_date, "Proposal has expired.");

    auto voter_for_itr = std::find (p_itr->voters_for.begin(), p_itr->voters_for.end(), voter);
    eosio_assert (voter_for_itr == p_itr->voters_for.end(), "User has already voted.");

    auto voter_against_itr = std::find (p_itr->voters_against.begin(), p_itr->voters_against.end(), voter);
    eosio_assert (voter_against_itr == p_itr->voters_against.end(), "User has already voted.");

    p_t.modify (p_itr, get_self(), [&](auto &p) {
        p.votes_against++;
        p.voters_against.push_back (voter);
    });
}

ACTION gyftietoken::calcgyft (name from, name to) 
{
    // eosio_assert (! is_paused(), "Contract is paused." );

    // require_auth (from);
    // eosio_assert (is_tokenholder (from), "Gyfter is not a GFT token holder.");

    // config_table config (get_self(), get_self().value);
    // auto c = config.get();

    // action(
    //     permission_level{get_self(), "owner"_n},
    //     c.token_gen, "generate"_n,
    //     std::make_tuple(from, getgftbalance (from), to))
    // .send();
}


ACTION gyftietoken::gyft (name from, 
                            name to, 
                            string idhash,
                            string relationship)
                            //string id_expiration) 
{
    eosio_assert (! is_paused(), "Contract is paused." );
    permit_account(from);

    require_auth (from);
    eosio_assert (is_tokenholder (from), "Gyfter must be a GFT token holder.");

    asset creation_fee = get_one_gft() * 0;
    if ( !is_account (to)) {
        creation_fee = create_account_from_request (from, to);
    }

    eosio_assert (!is_gyftie_account(to), "Receipient must not be a Gyftie account.");
    insert_profile (to, idhash);

    config_table config (get_self(), get_self().value);
    auto c = config.get();
   
    asset issue_to_gyfter = get_gyfter_reward(from);
    asset issue_to_gyftee = get_recipient_reward(); 

    string to_gyfter_memo { "Vouch-Gyft-Earn GFT-creation to Gyfter. See 'How Gyftie Works' document - ask us for link." };
    string to_gyftee_memo { "Vouch-Gyft-Earn GFT-creation to new user. See 'How Gyftie Works' document - ask us for link." };
    string to_gyftiegyftie {"Vouch-Gyft-Earn GFT-creation to Gyftie venture (gyftiegyftie). See 'How Gyftie Works' document - ask us for link."};
    string auto_liquidity_memo { "Vouch-Gyft-Earn GFT-creation to liquidity providers. See 'How Gyftie Works' document - ask us for link." };
 
    float share_for_liquidity_reward = 0.100000000000;
    asset gyft_inflation = issue_to_gyfter + issue_to_gyftee;
    asset amount_to_gyftiegyftie = asset { static_cast<int64_t> (gyft_inflation.amount * (1 - share_for_liquidity_reward)), issue_to_gyfter.symbol };
    asset liquidity_reward = gyft_inflation - amount_to_gyftiegyftie;

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "issue"_n,
        std::make_tuple(from, issue_to_gyfter - creation_fee, to_gyfter_memo))
    .send();

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "issue"_n,
        std::make_tuple(c.gyftie_foundation, amount_to_gyftiegyftie, to_gyftiegyftie))
    .send();

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "issue"_n,
        std::make_tuple(c.gftorderbook, liquidity_reward, auto_liquidity_memo))
    .send();

    action (
        permission_level{get_self(), "owner"_n},
        c.gftorderbook, "payliqinfrew"_n,
        std::make_tuple(liquidity_reward))
    .send();

    action (
        permission_level{get_self(), "owner"_n},
        get_self(), "issue"_n,
        std::make_tuple(to, issue_to_gyftee, to_gyftee_memo))
    .send();

    // Add 20% of Gyft'ed balance to the order book
    // asset auto_liquidity_add = adjust_asset (issue_to_gyftee, 0.20000000);
    // action (
    //     permission_level{get_self(), "owner"_n},
    //     get_self(), "transfer"_n,
    //     std::make_tuple(to, c.gftorderbook, auto_liquidity_add, auto_liquidity_memo))
    // .send();

    // action (
    //     permission_level{get_self(), "owner"_n},
    //     c.gftorderbook, "stacksell"_n,
    //     std::make_tuple(to, auto_liquidity_add))
    // .send();

    addgyft (from, to, issue_to_gyfter, issue_to_gyftee, relationship);
}

ACTION gyftietoken::ungyft(name account)
{
    require_auth (get_self());

    gyft_table g_t (get_self(), get_self().value);
    // auto gyftee_index = g_t.get_index<"bygyftee"_n>();
    // auto gyftee_itr = gyftee_index.find (account.value);
    // eosio_assert (gyftee_itr != gyftee_index.end(), "Gyft event not found for account.");

    // auto gyfter_index = g_t.get_index<"bygyfter"_n>();
    // auto gyfter_itr = gyfter_index.find (account.value);
    // eosio_assert (gyfter_itr == gyfter_index.end(), "Account issued a gyft; must ungyft downstream accounts first.");

    auto g_itr = g_t.begin();
    while (g_itr != g_t.end()) {
        eosio_assert (g_itr->gyfter != account, "Account issued a gyft; must ungyft downstream accounts first.");
        g_itr++;
    }

    bool found = false;
    g_itr = g_t.begin();
    while (g_itr != g_t.end() and !found) {
        if (g_itr->gyftee == account) {
            found = true;
        } else {
            g_itr++;
        }
    }

    // burn tokens for gyfter, gyftee, and gyftiegyftie
    burn (account, g_itr->gyftee_issue);
    burn (g_itr->gyfter, g_itr->gyfter_issue);

    config_table config (get_self(), get_self().value);
    auto c = config.get();
    burn (c.gyftie_foundation, g_itr->gyftee_issue + g_itr->gyfter_issue);

    profile_table p_t (get_self(), get_self().value);
    auto p_itr = p_t.find (account.value);
    eosio_assert (p_itr != p_t.end(), "Account profile is not found.");
    p_t.erase (p_itr);

    accounts a_t(get_self(), account.value);
    auto a_itr = a_t.find(g_itr->gyftee_issue.symbol.code().raw());
    eosio_assert (a_itr != a_t.end(), "Gyftee not found in accounts table under GFT symbol.");
    a_t.erase (a_itr);

    g_t.erase (g_itr);
}

ACTION gyftietoken::create()
{
    require_auth(get_self());

    symbol sym = symbol{symbol_code(GYFTIE_SYM_STR.c_str()), GYFTIE_PRECISION};

    eosio_assert(sym.is_valid(), "invalid symbol name");

    stats statstable(get_self(), sym.code().raw());
    auto existing = statstable.find(sym.code().raw());
    eosio_assert(existing == statstable.end(), "token with symbol already exists");

    statstable.emplace(get_self(), [&](auto &s) {
        s.symbol = sym;
        s.supply.symbol = sym;
        s.issuer = get_self();
    });

    insert_profile (get_self(), "ISSUER-HASH-PLACEHOLDER");
}

ACTION gyftietoken::issue(name to, asset quantity, string memo)
{
    auto sym = quantity.symbol;
    eosio_assert(sym.is_valid(), "invalid symbol name");
    eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");

    auto sym_name = sym.code().raw();
    stats statstable(_self, sym_name);
    auto existing = statstable.find(sym_name);
    eosio_assert(existing != statstable.end(), "token with symbol does not exist, create token before issue");
    const auto &st = *existing;

    eosio_assert (has_auth (st.issuer) || has_auth (get_self()), "issue requires authority of issuer or token contract.");
    
    eosio_assert(quantity.is_valid(), "invalid quantity");
    eosio_assert(quantity.amount > 0, "must issue positive quantity");
    eosio_assert(quantity.symbol == st.symbol, "symbol precision mismatch");

    statstable.modify(st, eosio::same_payer, [&](auto &s) {
        s.supply += quantity;
    });

    add_balance(st.issuer, quantity, st.issuer);

    if (to != st.issuer)
    {
        SEND_INLINE_ACTION(*this, transfer, {st.issuer, "owner"_n}, {st.issuer, to, quantity, memo});
    }
}

ACTION gyftietoken::transfer(name from, name to, asset quantity, string memo)
{
    eosio_assert (! is_paused(), "Contract is paused." );
    permit_account(from);
    
    eosio_assert(from != to, "cannot transfer to self");

    config_table config (get_self(), get_self().value);
    auto c = config.get();
    if (to == c.gftorderbook) {
        eosio_assert (has_auth (get_self()) || has_auth (from), "Permission denied - only token contract and token owner can transfer to order book.");
    } else {
        require_auth(from);
    }

    eosio_assert(is_account(to), "to account does not exist");    
    eosio_assert(is_gyftie_account(to) || c.gftorderbook == to || c.gyftie_foundation == to, "Recipient is not a Gyftie account. Must Gyft first.");
   
    if (to != c.gftorderbook || to != c.gyftie_foundation || to != get_self()) {
        availrating_table a_t (get_self(), to.value);
        auto a_itr = a_t.find (from.value);
        if (a_itr != a_t.end()) {
            a_t.modify (a_itr, get_self(), [&](auto &a) {
                a.rate_deadline = now() + (60 * 60 * 24);
            });
        } else {
            a_t.emplace (get_self(),  [&](auto &a) {
                a.ratee = from;
                a.rate_deadline = now() + (60 * 60 * 24);
            });
        }
    }

    auto sym = quantity.symbol.code().raw();
    stats statstable(_self, sym);
    const auto &st = statstable.get(sym);

    require_recipient(from);
    require_recipient(to);

    eosio_assert(quantity.is_valid(), "invalid quantity");
    eosio_assert(quantity.amount > 0, "must transfer positive quantity");
    eosio_assert(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
    eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");

    sub_balance(from, quantity);
    add_balance(to, quantity, get_self());
}

void gyftietoken::sub_balance(name owner, asset value)
{
    accounts from_acnts(_self, owner.value);

    const auto &from = from_acnts.get(value.symbol.code().raw(), "no balance object found");
    eosio_assert(from.balance.amount >= value.amount, "overdrawn balance");

    auto sym_name = value.symbol.code().raw();
    stats statstable(_self, sym_name);
    auto existing = statstable.find(sym_name);
    eosio_assert(existing != statstable.end(), "token with symbol does not exist, create token before issue");
    const auto &st = *existing;

    from_acnts.modify(from, get_self(), [&](auto &a) {
        a.balance -= value;
    });
}

void gyftietoken::add_balance(name owner, asset value, name ram_payer)
{
    accounts to_acnts(_self, owner.value);
    auto to = to_acnts.find(value.symbol.code().raw());
    if (to == to_acnts.end())
    {
        auto sym_name = value.symbol.code().raw();
        stats statstable(_self, sym_name);
        auto existing = statstable.find(sym_name);
        eosio_assert(existing != statstable.end(), "token with symbol does not exist, create token before issue");
        const auto &st = *existing;

        if (owner != st.issuer) {  // do not increment account count for issuer
            increment_account_count ();
        }
        to_acnts.emplace(ram_payer, [&](auto &a) {
            a.balance = value;
        });
    }
    else
    {
        to_acnts.modify(to, eosio::same_payer, [&](auto &a) {
            a.balance += value;
        });
    }
}


EOSIO_DISPATCH(gyftietoken, (setconfig)(delconfig)(create)(issue)(transfer)(calcgyft)(setcount)
                            (gyft)(propose)(votefor)(voteagainst)(pause)(unpause)(addrating)
                            (removeprop)(setcounter)(ungyft)(miggyftss1)(miggyftss2)
                            (nchallenge)(validate)(addcidnote)(addcnote))
                            // (copybal1)(remaccounts)(repopaccts)(remtemp)
